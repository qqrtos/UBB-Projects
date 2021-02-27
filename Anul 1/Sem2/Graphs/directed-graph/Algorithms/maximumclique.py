def isClique(graph, sample):
    for node1 in sample:
        for node2 in sample:
            if node1 != node2 and not graph.isEdge(node1, node2):
                return False
    return True


def getMaximumClique(graph):
    maxcliquesize = 0
    maxclique = []

    vertices = graph.IN.keys()

    for node in vertices:
        clique = [node]
        
        for other in graph.parseIn(node):
            clique.append(other)
            if not isClique(graph, clique):
                clique.pop(-1)

            if len(clique) > maxcliquesize:
                maxcliquesize = len(clique)
                maxclique = clique

    return maxclique
