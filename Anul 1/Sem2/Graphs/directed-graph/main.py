from UserInterface import UserInterface
from Graph.undirectedgraph import UndirectedGraph
from Graph.directedgraph import DirectedGraph
# from Algorithms.bellmanford import printShortestPath
from Graph.exceptions import AlgorithmFailed
from Algorithms.kruskal import kruskal
from Algorithms.maximumclique import *
from Algorithms.topologicalsort import DFStoposort, topologicalsorting
from Algorithms.dickstra import dickstra
from Algorithms.bellmanford import bellmanford

FILES = [
    "Tests/example.txt",
    "Tests/graph1k.txt",  # 0
    "Tests/graph10k.txt",  # 1
    "Tests/graph100k.txt",  # 2
    "Tests/graph1m.txt"  # 3
]

if __name__ == "__main__":
    ### Undirected graph DFS mini-test
    # g = UndirectedGraph("Tests/directed_example.txt")
    # print("\n\tUndirectedGraph\n" + str(g))
    # node = 0
    # print("DFS for the node " + str(node))
    # g.show_DFS_connectedVertices(node, [])

    testGraph = FILES[0]

    # graph = UndirectedGraph(testGraph)
    # maxclique = getMaximumClique(graph)
    # print(str(maxclique) + " -> size " + str(len(maxclique)))

    graph = DirectedGraph(testGraph)
    #print("Topological sort: " + str(topologicalsorting(graph)))
    print("Topological sort: " + str(DFStoposort(graph)))

    #graph = DirectedGraph(testGraph)
    #print(dickstra(graph, 0))
    # print(bellmanford(graph, 1))

    ### Kruskal alg.
    # mst, cost = kruskal(graph)
    # print("Kruskal\n" + str(mst) + " with cost: " + str(cost))

    print("\n\n\nDirected graph", end='')
    UI = UserInterface(DirectedGraph, testGraph)
    UI.startUI()
