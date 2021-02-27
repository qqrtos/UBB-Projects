from Graph.directedgraph import DirectedGraph
from Graph.exceptions import *
import unittest


class TestGraph(unittest.TestCase):
    def __init__(self):
        super().__init__()
        self.graph = DirectedGraph("graph1k.txt")

    def test_isVertex(self):
        self.assertEqual(self.graph.isVertex(1), True)
        self.assertEqual(self.graph.isVertex(1002), False)

    def test_AddVertex(self):
        initialNrVertices = self.graph.numberOfVertices

        # valid
        self.graph.addVertex(1001)
        self.assertEqual(self.graph.numberOfVertices, initialNrVertices + 1)
        self.assertEqual(self.graph.isVertex(1001), True)

        # invalid
        with self.assertRaises(DuplicateKeyError):
            self.graph.addVertex(0)

    def test_isEdge(self):
        self.assertEqual(self.graph.isEdge(0, 154), True)
        self.assertEqual(self.graph.isEdge(0, 500), False)

    def test_getCost(self):
        self.assertEqual(self.graph.getCost(2, 681), 40)
        self.assertNotEqual(self.graph.getCost(1, 5), 0)

    def test_setCost(self):
        self.graph.setCost(3, 706, 1)
        self.assertEqual(self.graph.getCost(3, 706), 1)

    def test_AddEdge(self):
        initialNrEdges = self.graph.numberOfEdges

        # valid
        self.graph.addEdge(0, 300, -1)
        self.assertEqual(self.graph.isEdge(0, 300), True)
        self.assertEqual(self.graph.getCost(0, 300), -1)
        self.assertEqual(self.graph.numberOfEdges, initialNrEdges + 1)

        # invalid
        with self.assertRaises(DuplicateKeyError):
            self.graph.addEdge(0, 154, 20)

    def test_removeEdge(self):
        initialNrEdges = self.graph.numberOfEdges

        # valid
        self.graph.removeEdge(0, 154)
        self.assertEqual(self.graph.isEdge(0, 154), False)
        self.assertEqual(self.graph.numberOfEdges, initialNrEdges - 1)

        # invalid
        with self.assertRaises(NotFoundError):
            self.graph.removeEdge(0, 100)
