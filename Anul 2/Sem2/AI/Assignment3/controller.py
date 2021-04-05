from repository import *


class Controller:
    def __init__(self, args):
        # args - list of parameters needed in order to create the controller
        self.__repository = args[0]
        self.__m = args[1]

    def iteration(self):
        # args - list of parameters needed to run one iteration
        # a iteration:
        # selection of the parrents
        # create offsprings by crossover of the parents
        # apply some mutations
        # selection of the survivors
        latestGeneration = self.__repository.getPopulationLast()
        parents = latestGeneration.selection(2)

        offspring1, offspring2 = parents[0].crossover(parents[1])
        newGeneration = latestGeneration

        newGeneration.addIndividual(offspring1)
        newGeneration.addIndividual(offspring2)
        newGeneration.mutate()
        newGeneration.evaluate()

        newGeneration.removeWeakest()
        newGeneration.removeWeakest()

        self.__repository.savePopulation(newGeneration)
        return newGeneration

    def run(self):
        # args - list of parameters needed in order to run the algorithm

        # until stop condition
        #    perform an iteration
        #    save the information need it for the satistics

        # return the results and the info for statistics
        noChanges = 0
        maxFitness = 0

        while True:
            gen = self.iteration()
            if gen.__maxFitness > maxFitness:
                maxFitness = gen.__maxFitness
                noChanges = 0
            else:
                noChanges += 1
                if noChanges >= 5:
                    break

        return gen

    def solver(self, args):
        # args - list of parameters needed in order to run the solver

        # create the population,
        # run the algorithm
        # return the results and the statistics
        self.__repository.clearPopulations()
        initialPopulation = Population(self.__repository.map, args[0],
                                       self.__repository.map.m * self.__repository.map.n, self.__m)
        initialPopulation.evaluate()
        self.__repository.savePopulation(initialPopulation)

        gen = self.run()

        best = gen.selection(1)[0]
        path = best.getPath()
        fitness = best._fit

        return [path, fitness]
