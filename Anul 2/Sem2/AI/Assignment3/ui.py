# -*- coding: utf-8 -*-


# imports
from gui import *
from controller import *
from repository import *
from domain import *
import threading
import matplotlib.pyplot as pyplot


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

class UI:
    def __init__(self, repository, controller):
        self.repo = repository
        self.controller = controller

    @staticmethod
    def showMapOptions():
        print("a. Create random map")
        print("b. Load map from file")
        print("c. Save current map")
        print("d. Visualize map")

    def displayMapMenu(self):
        options = {
            "a": self.repo.map.randomMap,
            "b": self.repo.loadMap,
            "c": self.repo.saveMap,
            "d": movingDrone
        }

        UI.showMapOptions()
        option = input("> ")
        while option != 'x':
            try:
                if option == "d":
                    threading.Thread(target=options[option],
                                     args=(self.repo.map,
                                           [[5, 7], [5, 8], [5, 9], [5, 10], [5, 11], [6, 11], [7, 11]],)).start()
                else:
                    options[option]()
            except Exception as e:
                print(e)

            UI.showMapOptions()
            option = input("> ")

    def visualizeStatistics(self):
        start = []
        print("Start: ")
        start.append(int(input(" x= ")))
        start.append(int(input(" y= ")))

        seed = [0, 11, 25, 100, 254, 91, 84, 1212, 542, 210,
                1232, 890, 12, 4, 21345, 310932, 123321, 54145, 1234, 11111,
                1337, 891834, 123423, 135633, 12343, 123432, 94747, 92921, 111, 13213444]

        f = []
        for s in seed:
            self.repo.setDomainSeed(s)
            info = self.controller.solver([start])
            f.append(info[1])

        x = [i for i in range(len(seed))]
        avg = np.average(f)
        stdDev = np.std(f)
        print("Average:{0}, StdDev:{1}".format(avg, stdDev))
        pyplot.plot(x, f)
        pyplot.show()

    @staticmethod
    def showEAOptions():
        print("a. Solve")
        print("b. Visualize statistics")

    def displayEAMenu(self):
        options = {
            "a": self.controller.solver,
            "b": self.visualizeStatistics
        }

        UI.showEAOptions()
        option = input("> ")
        while option != 'x':
            try:
                if option == "a":
                    start = []
                    print("Start point: ")
                    start.append(int(input(" x= ")))
                    start.append(int(input(" y= ")))
                    options[option]([start])
                else:
                    options[option]()
            except Exception as e:
                print(e)

            UI.showEAOptions()
            option = input("> ")


def main():
    repo = Repository()
    controller = Controller([repo, 5])
    ui = UI(repo, controller)

    print("\n1. Display map menu\n2. Display EA menu")
    option = input("> ")
    if option == "1":
        ui.displayMapMenu()
    elif option == "2":
        ui.displayEAMenu()


if __name__ == "__main__":
    main()
