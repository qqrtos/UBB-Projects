'''
Command based:
    mark 1 1
    step 1 1
'''
from texttable import Texttable
import random


class SteppedOnMineException(Exception):
    pass


class Field:
    '''
    Represents one square in the minefield.
    Has coordinates and a state (mine or non-mine).
    '''

    def __init__(self, x, y, state):
        self._x = x
        self._y = y
        self._state = state
        self._revealed = False

    @property
    def x(self):
        return self._x

    @property
    def y(self):
        return self._y

    @property
    def state(self):
        return self._state

    @property
    def revealed(self):
        return self._revealed

    def reveal(self):
        self._revealed = True


class Board:
    def __init__(self, width, height, mines):
        # ++validation

        self._width = width
        self._height = height
        self._mines = mines

        # initialize the board
        self._data = []
        for i in range(self._height):
            self._data.append([0] * self._width)

        # lay the mines
        self._layMines()

        # compute the number of neighbour mines
        self._computeNeighbours()

    def _layMines(self):
        indices = list(range(0, self._width * self._height))
        for i in range(self._mines):
            val = random.choice(indices)
            indices.remove(val)
            self._data[val // self._width][val % self._width] = -1

    def __str__(self):
        t = Texttable()
        for i in range(self._height):
            t.add_row(self._data[i])
        return t.draw()

    def _neighbours(self, x, y):
        w = self._width
        h = self._height
        res = []

        res.append((x - 1, y - 1))
        res.append((x - 1, y))
        res.append((x - 1, y + 1))
        res.append((x, y - 1))
        res.append((x, y + 1))
        res.append((x + 1, y - 1))
        res.append((x + 1, y))
        res.append((x + 1, y + 1))

        poz = 0
        while poz < len(res):
            sq = res[poz]
            if sq[0] < 0 or sq[0] >= h or sq[1] < 0 or sq[1] >= w:
                res.remove(sq)
            else:
                poz += 1

        return res

    def _computeNeighbours(self):
        for x in range(self._height):
            for y in range(self._width):
                if self._data[x][y] == -1:
                    continue
                mines = 0
                for ng in self._neighbours(x, y):
                    if self._data[ng[0]][ng[1]] == -1:
                        mines += 1
                self._data[x][y] = mines

    def move(self, x, y):
        # validate move
        if x < 0 or x >= self._height or y < 0 or y >= self._width:
            raise ValueError("Step in the minefield!")

        if self._data[x][y] == -1:
            raise SteppedOnMineException()

        # implement fill for squares that are 0

        pass


b = Board(6, 5, 7)
print('Neighbours: ' + str(b._neighbours(2, 5)))
print(b)
