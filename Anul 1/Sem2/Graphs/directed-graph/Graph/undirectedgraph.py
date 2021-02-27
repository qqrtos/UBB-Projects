from Graph.exceptions import *
from Graph.directedgraph import DirectedGraph


class UndirectedGraph(DirectedGraph):
    def __init__(self, file=""):
        super().__init__("")
        self.readFromFile(file)

    def readFromFile(self, file):
        """
            Reads the graph from a file.
            :param file: Path to the file
            :return: -
        """
        with open(file, "r") as f:
            nrOfVertices, _ = [int(_) for _ in f.readline().split()]

            for i in range(nrOfVertices):
                self.addVertex(i)

            while (line := f.readline()) != "":
                start, dest, cost = [int(_) for _ in line.strip().split()]
                self.addEdge(start, dest, cost)

    def addEdge(self, start, dest, cost):
        """
        Add the edge (start<->dest) to the graph.
        :param cost: cost of the edge
        :return: raises duplicateKeyError if the edge is already in the graph.
        """
        if self.isEdge(start, dest) and self.isEdge(dest, start):
            raise DuplicateKeyError("Cannot add the same edge twice")

        self._IN[dest].append(start)
        self._OUT[start].append(dest)
        self._IN[start].append(dest)
        self._OUT[dest].append(start)

        self._costs[(start, dest)] = cost
        self._costs[(dest, start)] = cost

        self._nrOfEdges += 1

    def getEdges(self):
        edges = []
        for each in self._costs:
            if (each[1], each[0], self._costs[each]) not in edges:
                edges.append((each[0], each[1], self._costs[each]))
        return edges

    def show_DFS_connectedVertices(self, vertex, visited=[]):
        '''
        Show all connected nodes to the given vertex.
        :param vertex: Given vertex
        :param visited: A list of all the currently visited vertices.
        :return: -
        '''
        print(vertex, end=" ")
        visited.append(vertex)
        for neighbour in self.parseOut(vertex):
            if neighbour not in visited:
                self.show_DFS_connectedVertices(neighbour, visited)

    def __str__(self):
        graphStr = ""

        checked = []  # keep track of visited nodes
        for i in list(self._IN.keys()):
            if len(self._IN[i]) == len(self._OUT[i]) == 0:
                graphStr += str(i) + " - isolated vertex." + '\n'
            else:
                for j in self._OUT[i]:
                    if j not in checked:
                        graphStr += str(i) + " <-> " + str(j) + " has cost " + str(self._costs[(i, j)]) + '\n'
            checked.append(i)

        return graphStr
