# -*- coding: utf-8 -*-

# Creating some colors
BLUE = (0, 0, 255)
GRAYBLUE = (50, 120, 120)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)

# define directions
UP = 0
DOWN = 2
LEFT = 1
RIGHT = 3

# define indexes variations
DIRECTIONS = [[-1, 0], [1, 0], [0, 1], [0, -1]]
DIRECTIONS_DICT = {
    UP: DIRECTIONS[0],
    DOWN: DIRECTIONS[1],
    RIGHT: DIRECTIONS[2],
    LEFT: DIRECTIONS[3]
}

# define mapsize
mapLengh = 20

# map file
MAP_FILE = "test.map"
