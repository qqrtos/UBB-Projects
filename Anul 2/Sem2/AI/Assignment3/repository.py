# -*- coding: utf-8 -*-

import pickle
from domain import *

def setSeed(val):
    np.random.seed(val)

class Repository:
    def __init__(self):
        self.__populations = []
        self.map = Map()

    def setDomainSeed(self, x):
        setSeed(x)

    def createPopulation(self, args):
        # args = [populationSize, individualSize] -- you can add more args    
        return Population(args[0], args[1])

    def getLastPopulation(self):
        return self.__populations[-1]

    def savePopulation(self, pop):
        return self.__populations.append(pop)

    def clearPopulations(self):
        self.__populations.clear()

    def loadMap(self, file=MAP_FILE):
        with open(file, "rb") as f:
            loadedObj = pickle.load(f)
            self.map = Map(loadedObj.n, loadedObj.m, loadedObj.surface)

    def saveMap(self, file=MAP_FILE):
        with open(file, 'wb') as f:
            pickle.dump(self.map, f)
            f.close()