
def PrimsAlg(graph, vertex):
    #list of all vertices
    vertices = graph.parseVertices()
    #dictionary containing all edges <(vertex1,vertex2),cost>
    costs = graph.parseEdges()

    #list of visited nodes
    visited = []
    visited.append(vertex)
    #list of visited edges
    visitedEdges = []

    totalCost = 0

    #while the two lists are not identical, search for the minimum edge and add it to the list
    while len(visited) != len(vertices):
        minEdges = {}
        for edge in costs.keys():
            if edge[0] in visited and edge[1] not in visited:
                minEdges[edge] = costs[edge]
            elif edge[1] in visited and edge[0] not in visited:
                minEdges[(edge[1], edge[0])] = costs[edge]

        minPos = min(minEdges, key=minEdges.get)
        totalCost += minEdges[minPos]
        visited.append(minPos[1])
        visitedEdges.append(minPos)
    print("starting vertex:", vertex, visitedEdges, "and the cost is:", totalCost)
