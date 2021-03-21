
def searchAStar(mapM, droneD, initialX, initialY, finalX, finalY):
    # TO DO
    # implement the search function and put it in controller
    # returns a list of moves as a list of pairs [x,y]

    pass


def searchGreedy(mapM, droneD, initialX, initialY, finalX, finalY):
    # TO DO
    # implement the search function and put it in controller
    # returns a list of moves as a list of pairs [x,y]

    result = []

    x, y = initialX, initialY
    visited = {(initialX, initialY): True}

    while (not (x == finalX and y == finalY)) and (x, y) not in result:
        result.append((x, y))
        # droneD.move()

        if x < finalX and y < finalY and x < 19 and y < 19 and mapM.surface[x + 1][y + 1] == 0 and \
                visited.get((x + 1, y + 1)) is None:
            visited[(x + 1, y + 1)] = True
            x += 1
            y += 1
        elif x > finalX and y > finalY and x > 0 and y > 0 and mapM.surface[x - 1][y - 1] == 0 and \
                visited.get((x - 1, y - 1)) is None:
            visited[(x - 1, y - 1)] = True
            x -= 1
            y -= 1
        elif x > finalX and x > 0 and mapM.surface[x - 1][y] == 0 and visited.get((x - 1, y)) is None:
            visited[(x - 1, y)] = True
            x -= 1
        elif y > finalY and y > 0 and mapM.surface[x][y - 1] == 0 and visited.get((x, y - 1)) is None:
            visited[(x, y - 1)] = True
            y -= 1
        elif x < finalX and x < 19 and mapM.surface[x + 1][y] == 0 and visited.get((x + 1, y)) is None:
            visited[(x + 1, y)] = True
            x += 1
        elif y < finalY and y < 19 and mapM.surface[x][y + 1] == 0 and visited.get((x, y + 1)) is None:
            visited[(x, y + 1)] = True
            y += 1

    return result


def dummySearch():
    # example of some path in test1.map from [5,7] to [7,11]
    return [[5, 7], [5, 8], [5, 9], [5, 10], [5, 11], [6, 11], [7, 11]]
