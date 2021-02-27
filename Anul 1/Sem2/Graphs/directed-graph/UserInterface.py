from Graph.directedgraph import createRandomGraph
from Graph.exceptions import *


class UserInterface:
    def __init__(self, graphConstructor, fileName):
        self.graph = graphConstructor(fileName)

    @staticmethod
    def printMenu():
        print("\n\t1. Add a vertex")
        print("\t2. Remove a vertex")
        print("\t3. Check if a vertex exists")
        print("\t4. Get the number of vertices")
        print("\t5. Parse the inbound neighbours of a vertex")
        print("\t6. Parse the outbound neighbours of a vertex")
        print("\t7. Add an edge")
        print("\t8. Remove an edge")
        print("\t9. Get number of edges")
        print("\t10. Check if an edge exists")
        print("\t11. Get the cost of an edge")
        print("\t12. Modify the cost of an edge")
        print("\t13. Print the graph")

        print("\t14. Create random graph")

        print("\tx. Exit app\n")

    def startUI(self):
        while True:
            self.printMenu()

            cmd = input(">")
            try:
                if cmd == '1':
                    vertex = int(input("Vertex: "))
                    self.graph.addVertex(vertex)
                elif cmd == '2':
                    vertex = int(input("Vertex: "))
                    self.graph.removeVertex(vertex)
                elif cmd == '3':
                    vertex = int(input("Vertex: "))
                    if self.graph.isVertex(vertex):
                        print(str(vertex) + " is a vertex")
                    else:
                        print(str(vertex) + " isn't a vertex")
                elif cmd == '4':
                    print("The graph has " + str(self.graph.numberOfVertices) + " vertices")
                elif cmd == '5':
                    vertex = int(input("Vertex: "))
                    print(self.graph.parseIn(vertex))
                elif cmd == '6':
                    vertex = int(input("Vertex: "))
                    print(self.graph.parseOut(vertex))
                elif cmd == '7':
                    start, dest, cost = [int(_) for _ in input("-->").strip().split()]
                    self.graph.addEdge(start, dest, cost)
                elif cmd == '8':
                    start, dest = [int(_) for _ in input("-->").strip().split()]
                    self.graph.removeEdge(start, dest)
                elif cmd == '9':
                    print("The graph has " + str(self.graph.numberOfEdges) + " edges")
                elif cmd == '10':
                    start, dest = [int(_) for _ in input("-->").strip().split()]
                    if (self.graph.isEdge(start, dest)):
                        print(str(start) + " - " + str(dest) + " is an edge")
                elif cmd == '11':
                    start, dest = [int(_) for _ in input("-->").strip().split()]
                    print("The edge " + str(start) + ' - ' + str(dest) + " has the cost " + str(
                        self.graph.getCost(start, dest)))
                elif cmd == '12':
                    start, dest, newCost = [int(_) for _ in input("-->").strip().split()]
                    self.graph.setCost(start, dest, newCost)
                elif cmd == '13':
                    print(self.graph)
                elif cmd == '14':
                    vertices, edges = [int(_) for _ in input("-->").strip().split()]
                    newRandomGraph = createRandomGraph(vertices, edges)
                    print(newRandomGraph)
                elif cmd == 'x':
                    break
            except (DuplicateKeyError, NotFoundError) as grapherror:
                print(grapherror)
            except:
                print("Input error")
