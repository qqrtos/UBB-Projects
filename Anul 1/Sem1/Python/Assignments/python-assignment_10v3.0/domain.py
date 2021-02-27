from texttable import Texttable
from random import randint


class GameError(Exception):
    '''
    Custom error for my game.
    '''

    def __init__(self, message):
        super().__init__(message)


class Board:
    def __init__(self, rows, columns):
        self._rows = rows
        self._columns = columns
        self._board = self._initBoard()
        self._moves = 0

    @property
    def rows(self):
        return self._rows

    @property
    def cols(self):
        return self._columns

    @property
    def board(self):
        return self._board

    def _initBoard(self):
        board = []
        for i in range(self.cols):
            board.append([0] * self.rows)
        return board

    def _fullColumn(self, col):
        '''
        Checks whether a column is full or not.
        Return: True/False
        '''
        for col in self._board:
            if 0 in col:
                return False
        return True

    def __str__(self):
        '''
        Transform the board into a table drawable in the console.
        '''
        t = Texttable()
        d = {0: ' ', 1: 'X', -1: 'O'}
        for row in self._board:
            toDraw = []
            for element in row:
                toDraw += d[element]
            t.add_row(toDraw)
        return t.draw()

    def move(self, col, player):
        '''
        Make a valid move on the board
        '''
        if col >= self.cols or col < 0:
            raise GameError("Move outside the board.")

        if self._fullColumn(col):
            raise GameError("Column is full.")

        d = {'P': 1, 'C': -1}
        self._moves += 1
        row = self._board[col].index(0)
        self._board[row][col] = d[player]

    def won(self, row, col):
        '''
        Return True if someone won. False otherwise.
        '''
        # sum of values on the same line
        # determine left border (right border is the given column)
        if col < 4:
            minCol = 0
        else:
            minCol = col - 4
        maxCol = self.cols - 5
        for column in range(minCol, maxCol + 1):
            # calculates the sum for each set of 5 consecutive elements (on row 'row') that contain square (r, c)
            lineSum = 0
            for i in range(5):
                lineSum += self.board[row][column + i]
            if abs(lineSum) == 5:
                return True

        # sum of the values on the same column
        if row < 4:
            minRow = 0
        else:
            minRow = row - 4
        maxRow = self.rows - 5
        for eachRow in range(minRow, maxRow + 1):
            # calculates the sum for each set of 5 consecutive elements (on column 'col') that contain square (r, c)
            colSum = 0
            for i in range(5):
                colSum += self.board[eachRow + i][col]
            if abs(colSum) == 5:
                return True

        # minRow and minCol are already determined
        while minRow != maxRow and minCol != maxCol:
            diagSum = 0
            for i in range(5):
                diagSum += self.board[minRow + i][minCol + i]
            if abs(diagSum) == 5:
                return True
            minRow += 1
            minCol += 1

        return False  # no one won yet


class Computer:
    def __init__(self, board):
        self._board = board

    def giveCoordinates(self):
        col = randint(0, self._board.columns - 1)
        while self._board.fullColumn(col):
            col = randint(0, self._board.columns - 1)
        return col


class Game:
    def __init__(self, board, computer):
        self._board = board
        self._computer = computer

    @property
    def board(self):
        return self._board

    def playerMove(self, col):
        try:
            col = int(col)
        except:
            raise GameError("Column should be an integer.")
        self.board.move(col, 'P')

    def computerMove(self):
        move = self._computer.giveCoordinates()
        self.board.move(move, 'C')
