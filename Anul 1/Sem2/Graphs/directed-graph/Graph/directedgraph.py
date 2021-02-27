from copy import deepcopy
from Graph.exceptions import *
import random


class DirectedGraph:
    def __init__(self, file=""):
        self._IN = {}
        self._OUT = {}
        self._costs = {}

        self._nrOfVertices = 0
        self._nrOfEdges = 0

        self._edges = []

        if file != "":
            self.readFromFile(file)

    def readFromFile(self, file):
        '''
        Reads the graph from a file.
        :param file: Path to the file
        :return: -
        '''
        with open(file, "r") as f:
            nrOfVertices, nrOfEdges = [int(_) for _ in f.readline().split()]

            for i in range(nrOfVertices):
                self.addVertex(i)

            while (line := f.readline()) != "":
                start, dest, cost = [int(_) for _ in line.strip().split()]
                self._edges.append((start, dest))
                self.addEdge(start, dest, cost)

    @property
    def IN(self):
        return deepcopy(self._IN)

    @property
    def OUT(self):
        return deepcopy(self._OUT)

    @property
    def costs(self):
        return deepcopy(self._costs)

    @property
    def numberOfVertices(self):
        return self._nrOfVertices

    @property
    def numberOfEdges(self):
        return self._nrOfEdges

    def parseIn(self, vertex):
        '''
        Return a list of inbound neighbours for the given vertex.
        :param vertex: given vertex
        :return: a list of inbound neighbours
        '''
        if not self.isVertex(vertex):
            raise NotFoundError("Invalid vertex")
        return self._IN[vertex]

    def parseOut(self, vertex):
        '''
            Return a list of outbound neighbours for the given vertex.
            :param vertex: given vertex
            :return:
        '''
        if not self.isVertex(vertex):
            raise NotFoundError("Invalid vertex")
        return self._OUT[vertex]

    def isEdge(self, start, dest):
        '''
        Check wheter there exists an edge start->dest
        :param start: starting position
        :param dest: destination
        :return: True - edge exists
                 False - otherwise
        '''
        try:
            for i in self._OUT[start]:
                if i == dest:
                    return True
        except:
            pass
        return False

    def addEdge(self, start, dest, cost):
        # add a vertex from start to dest with the cost = cost
        if self.isEdge(start, dest):
            raise DuplicateKeyError("Cannot add the same edge twice")

        self._IN[dest].append(start)
        self._OUT[start].append(dest)

        self._costs[(start, dest)] = cost
        self._nrOfEdges += 1

    def removeEdge(self, start, dest):
        '''
        Remove the edge start->dest
        :param start: starting vertex
        :param dest: destination vertex
        :return: -
        '''
        if not self.isEdge(start, dest):
            raise NotFoundError("Cannot remove an inexistent edge")

        self._IN[dest].remove(start)
        self._OUT[start].remove(dest)

        del self._costs[(start, dest)]
        self._nrOfEdges -= 1

    def isVertex(self, vertex):
        '''
        Check whether there exists a vertex in the graph.
        :param vertex: given vertex
        :return: True - vertex exists
                 False - otherwise
        '''
        if vertex in list(self._IN.keys()):
            return True
        return False

    def addVertex(self, vertex):
        '''
        Add a vertex to the graph.
        :return: raises exception if the vertex is a duplicate
        '''
        if self.isVertex(vertex):
            raise DuplicateKeyError("Cannot add the same vertex twice")

        self._IN[vertex] = []
        self._OUT[vertex] = []
        self._nrOfVertices += 1

    def removeVertex(self, vertex):
        '''
        Remove a vertex from the graph.
        :return: raises exception if the vertex is not part of the graph.
        '''
        if not self.isVertex(vertex):
            raise NotFoundError("Vertex not found")

        for i in self.parseIn(vertex):
            self.removeEdge(i, vertex)

        for i in self.parseOut(vertex):
            self.removeEdge(vertex, i)

        del self._IN[vertex]
        del self._OUT[vertex]
        self._nrOfVertices -= 1

    def getCost(self, start, dest):
        '''
        Get the cost of a given edge.
        :return: the cost of that edge (if it exists)
                 Raises exception otherwise
        '''
        if not self.isEdge(start, dest):
            raise NotFoundError("Edge not in the graph")
        return self._costs[(start, dest)]

    def setCost(self, start, dest, newCost):
        if not self.isEdge(start, dest):
            raise NotFoundError("Edge not in the graph")
        self._costs[(start, dest)] = newCost

    def __str__(self):
        graphStr = ""

        for i in list(self._IN.keys()):
            if len(self._IN[i]) == len(self._OUT[i]) == 0:
                graphStr += str(i) + " - isolated vertex." + '\n'
            else:
                for j in self._OUT[i]:
                    graphStr += str(i) + " -> " + str(j) + " has cost " + str(self._costs[(i, j)]) + '\n'

        return graphStr


def createRandomGraph(vertices, edges):
    graph = DirectedGraph()

    for i in range(1, vertices + 1):
        graph._IN[i] = []
        graph._OUT[i] = []

    addedEdges = 0
    while addedEdges < edges:
        x = random.randrange(1, vertices + 1)
        y = random.randrange(1, vertices + 1)
        cost = random.randint(-10, 15)

        if not graph.isEdge(x, y):
            graph.addEdge(x, y, cost)
            addedEdges += 1

    return graph
