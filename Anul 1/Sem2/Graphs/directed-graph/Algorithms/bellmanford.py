def bellmanford(graph, start):
    dist = {}
    prev = {}

    for each in graph.IN:
        dist[each] = 99999999

    dist[start] = 0
    changed = True

    while changed:
        changed = False

        for e in graph._edges:
            if dist[e[1]] > dist[e[0]] + graph.getCost(e[0], e[1]):
                dist[e[1]] = dist[e[0]] + graph.getCost(e[0], e[1])
                prev[e[1]] = e[0]
                changed = True

    return dist, prev
