from texttable import Texttable
from random import randint
from random import choice
import pickle


class GameError(Exception):
    def __init__(self, msg):
        super().__init__(msg)


class Board:
    def __init__(self):
        self._moves = 0
        self._init_board()

    @property
    def moves(self):
        return self._moves

    @property
    def board(self):
        return self._board

    def _init_board(self):
        self._board = []
        for _ in range(6):
            self._board.append([0] * 6)

    def __str__(self):
        table = Texttable()
        symbolDict = {1: 'O', -1: 'X', 0: ' '}

        for i in range(6):
            newRow = []
            for j in range(6):
                newRow.append(symbolDict[self._board[i][j]])
            table.add_row(newRow)

        return table.draw()

    def _isValidMove(self, row, col):
        if row >= 6 or col >= 6 or row < 0 or col < 0:
            return False
        if self._board[row][col] != 0:
            return False
        return True

    def isFull(self):
        return self._moves == 6 * 6

    def move(self, row, col, symbol):
        symbolDict = {'X': -1, 'O': 1}
        if not self._isValidMove(row, col):
            raise GameError("Invalid move.")
        self._board[row][col] = symbolDict[symbol]
        self._moves += 1

    def won(self):
        if self.isFull():
            return True, 'Computer'

        # check lines
        b = self.board
        for i in range(6):
            # check lines
            if abs(b[i][0] + b[i][1] + b[i][2] + b[i][3] + b[i][4]) == 5:
                return (True, 'Player')
            if abs(b[i][1] + b[i][2] + b[i][3] + b[i][4] + b[i][5]) == 5:
                return (True, 'Player')

            # check columns
            if abs(b[0][i] + b[1][i] + b[2][i] + b[3][i] + b[4][i]) == 5:
                return (True, 'Player')
            if abs(b[1][i] + b[2][i] + b[3][i] + b[4][i] + b[5][i]) == 5:
                return (True, 'Player')

        # main diagonal
        if abs(b[0][0] + b[1][1] + b[2][2] + b[3][3] + b[4][4]) == 5:
            return (True, 'Player')
        if abs(b[1][1] + b[2][2] + b[3][3] + b[4][4] + b[5][5]) == 5:
            return (True, 'Player')

        # second diagonal
        if abs(b[0][5] + b[1][4] + b[2][3] + b[3][2] + b[4][1]) == 5:
            return (True, 'Player')
        if abs(b[1][4] + b[2][3] + b[3][2] + b[4][1] + b[5][0]) == 5:
            return (True, 'Player')

        return (False, None)


class Computer:
    def __init__(self, board):
        self._board = board

    @property
    def board(self):
        return self._board

    def move(self):
        for i in range(6):
            for j in range(6):
                if self.board.board[i][j] == 0:
                    self.board.board[i][j] = -1
                    won, _ = self.board.won()
                    if won:
                        self.board.board[i][j] = 1
                        return

                    self.board.board[i][j] = 1
                    won, _ = self.board.won()
                    if won:
                        self.board.board[i][j] = -1
                        return

                    self.board.board[i][j] = 0

        row = randint(0, 6)
        col = randint(0, 6)
        symbol = choice(['X', 'O'])

        while not self.board._isValidMove(row, col):
            row = randint(0, 6)
            col = randint(0, 6)

        self.board.move(row, col, symbol)


class Game:
    def __init__(self, board, computer):
        self._computer = computer
        self._board = board

    @property
    def board(self):
        return self._board

    @property
    def computer(self):
        return self._computer

    def saveGame(self):
        with open('game.txt', 'wb') as fopen:
            pickle.dump(self.board, fopen)
        exit(0)

    def loadGame(self):
        with open('game.txt', 'rb') as fopen:
            self._board = pickle.load(fopen)

    def computerMove(self):
        self.computer.move()

    def playerMove(self, row, col, symbol):
        self.board.move(row, col, symbol)

    def won(self):
        return self.board.won()
