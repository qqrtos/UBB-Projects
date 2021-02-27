from queue import PriorityQueue


def dickstra(graph, start):
    prev = {}
    dist = {start: 0}
    q = PriorityQueue()
    q.put((0, start))

    while not q.empty():
        x = q.get()[1]
        for y in graph.parseOut(x):
            if y not in dist.keys() or dist[x] + graph.getCost(x, y) < dist[y]:
                dist[y] = dist[x] + graph.getCost(x, y)
                q.put((dist[y], y))
                prev[y] = x

    return prev, dist
