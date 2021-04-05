# -*- coding: utf-8 -*-

from random import *
from utils import *
import numpy as np


# the glass gene can be replaced with int or float, or other types
# depending on your problem's representation

class Gene:
    def __init__(self, direction=None):
        if direction is None:
            self.direction = np.random.randint(0, len(DIRECTIONS))
        else:
            self.direction = direction

    def __eq__(self, other):
        return self.direction == other.direction

    def __hash__(self):
        return hash(self.direction)


class Individual:
    def __init__(self, map, startPos, size=0):
        self._size = size
        self._x = [Gene() for _ in range(self._size)]
        self._fit = None
        self._map = map
        self._start = startPos

    def fitness(self):
        exploredPoints = [self._start]
        prev = self._start

        penalty = 0

        for gene in self._x:
            dir = DIRECTIONS_DICT[gene.direction]
            genePos = [prev[0] + dir[0], prev[1] + dir[1]]
            exploredPoints.append(genePos)

            prev = genePos

            if not (0 <= genePos[0] < self._map.n and
                    0 <= genePos[1] < self._map.m and
                    self._map.surface[genePos[0]][genePos[1]] == 0):
                penalty += 1

            for i in range(len(DIRECTIONS)):
                t = DIRECTIONS[i]
                p = [genePos[0] + t[0], genePos[1] + t[1]]

                while (0 <= p[0] < self._map.n
                       and 0 <= p[1] <= self._map.m
                       and self._map.surface[p[0]][p[1]] == 0
                       and not p in exploredPoints):
                    exploredPoints.append(p)
                    p = [p[0] + t[0], p[1] + t[1]]

        self._fit = len(exploredPoints) - penalty * 10

    def mutate(self, mutateProbability=0.04):
        for i in range(len(self._x)):
            if random() < mutateProbability:
                indx = np.random.randint(0, len(DIRECTIONS))
                self._x[i] = Gene(DIRECTIONS[indx])

    def getPath(self):
        path = []
        previous = self._start
        path.append(self._start)
        for g in self._x:
            d = DIRECTIONS_DICT[g.direction]
            genePos = [previous[0] + d[0], previous[1] + d[1]]
            previous = genePos
            path.append(genePos)
        return path

    def crossover(self, otherParent, crossoverProbability=0.8):
        offspring1, offspring2 = Individual(self._map, self._start, self._size), Individual(self._map, self._start,
                                                                                            self._size)
        if random() < crossoverProbability:
            offspring1._x.clear()
            offspring2._x.clear()

            nextCut = np.random.randint(1, self._size - 1)
            prevCut = 0

            k = True
            while nextCut < self._size - 1:
                if k:
                    for e in self._x[prevCut:nextCut]:
                        offspring1._x.append(e)
                    for e in otherParent.getX()[prevCut:nextCut]:
                        offspring2._x.append(e)
                else:
                    for e in self._x[prevCut:nextCut]:
                        offspring2._x.append(e)
                    for e in otherParent.getX()[prevCut:nextCut]:
                        offspring1._x.append(e)

                k = not k
                prevCut = nextCut
                nextCut = np.random.randint(prevCut + 1, self._size)

            while (s := offspring1._size) < self._size:
                offspring1._x.append(self._x[s])
                offspring2._x.append(otherParent._x[s])

        return offspring1, offspring2


class Population:
    def __init__(self, map, start, populationSize=0, individualSize=0):
        self.__map = map
        self.__populationSize = populationSize
        self.__v = [Individual(map, start, individualSize) for _ in range(populationSize)]
        self.__maxFitness = 0

    def removeWeakness(self):
        weakest = min(self.__v, key=lambda i: i.getF())
        self.__v.remove(weakest)

    def addIndividual(self, individual):
        self.__v.append(individual)

    def mutate(self):
        for x in self.__v:
            x.mutate()

    def evaluate(self):
        for x in self.__v:
            x.fitness()
            if x._fit > self.__maxFitness:
                self.__maxFitness = x._fit

    def selection(self, k=0):
        if k == 0:
            return []

        e = self.__v[:]
        e.sort(key=lambda x: x._fit, reverse=True)

        return e[:k]


class Map:
    def __init__(self, n=20, m=20, surface=None):
        self.n = n
        self.m = m
        if surface is None:
            self.surface = np.zeros((self.n, self.m))
        else:
            self.surface = surface

    def randomMap(self, fill=0.2):
        for i in range(self.n):
            for j in range(self.m):
                if random() <= fill:
                    self.surface[i][j] = 1

    def __str__(self):
        string = ""
        for i in range(self.n):
            for j in range(self.m):
                string = string + str(int(self.surface[i][j]))
            string = string + "\n"
        return string
