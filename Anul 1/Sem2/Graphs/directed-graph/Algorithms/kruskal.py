from Graph import undirectedgraph


def findParent(parentsList, vertex):
    # find the parent of a node
    if parentsList[vertex] == vertex:
        return vertex
    else:
        return findParent(parentsList, parentsList[vertex])


def mergeTrees(parent, ranks, v1, v2):
    # merge two trees
    v1Root = findParent(parent, v1)
    v2Root = findParent(parent, v2)

    if ranks[v1Root] > ranks[v2Root]:
        parent[v2Root] = v1Root
    elif ranks[v1Root] < ranks[v2Root]:
        parent[v1Root] = v2Root
    else:
        parent[v2Root] = v1Root
        ranks[v1Root] += 1


def kruskal(graph):
    edges = graph.getEdges()
    edges = sorted(edges, key=lambda c: c[2])

    finalCost = 0

    parents = []
    ranks = []
    for i in range(graph.numberOfVertices):
        parents.append(i)
        ranks.append(0)

    result = []

    index = 0
    while len(result) < graph.numberOfVertices - 1 and index < graph.numberOfEdges:
        start, dest, cost = edges[index]

        index += 1

        startRoot = findParent(parents, start)
        destRoot = findParent(parents, dest)

        if startRoot != destRoot:
            result.append((start, dest))#, cost))
            finalCost += cost
            mergeTrees(parents, ranks, start, dest)

    return result, finalCost
