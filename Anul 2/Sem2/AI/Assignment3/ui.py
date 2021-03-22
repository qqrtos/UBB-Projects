# -*- coding: utf-8 -*-


# imports
from gui import *
from controller import *
from repository import *
from domain import *
import threading


# create a menu
#   1. map options:
#         a. create random map
#         b. load a map
#         c. save a map
#         d visualise map
#   2. EA options:
#         a. parameters setup
#         b. run the solver
#         c. visualise the statistics
#         d. view the drone moving on a path
#              function gui.movingDrone(currentMap, path, speed, markseen)
#              ATENTION! the function doesn't check if the path passes trough walls

def displayMenu():
    print("a. Create random map")
    print("b. Load map from file")
    print("c. Save current map")
    print("d. Visualize map")


def main():
    map = Map()
    options = {
        "a": map.randomMap,
        "b": map.loadMap,
        "c": map.saveMap,
        "d": movingDrone
    }

    displayMenu()
    option = input("> ")
    while option != 'x':
        try:
            if option == "d":
                threading.Thread(target=options[option], args=(map, [[5, 7], [5, 8], [5, 9], [5, 10], [5, 11], [6, 11], [7, 11]],)).start()
            else:
                options[option]()
        except Exception as e:
            print(e)

        displayMenu()
        option = input("> ")


if __name__ == "__main__":
    main()
