from queue import Queue


def topologicalsorting(graph):
    sorted = []
    q = Queue()
    count = {}

    for each in graph.IN:
        count[each] = len(graph.IN[each])
        if count[each] == 0:
            q.put(each)

    while not q.empty():
        current = q.get()
        sorted.append(current)

        for each in graph.parseOut(current):
            count[each] -= 1
            if count[each] == 0:
                q.put(each)

    return sorted


def helpDFS(graph, v, sorted, fullyprocessed, inprocess):
    inprocess.add(v)

    for each in graph.parseIn(v):
        if each in inprocess:
            return False
        elif each not in fullyprocessed:
            ok = helpDFS(graph, each, sorted, fullyprocessed, inprocess)
            if not ok:
                return False

    inprocess.remove(v)
    sorted.append(v)
    fullyprocessed.add(v)
    return True


def DFStoposort(graph):
    sorted = []
    fullyprocessed = set()
    inprocess = set()

    for each in graph.IN:
        if each not in fullyprocessed:
            ok = helpDFS(graph, each, sorted, fullyprocessed, inprocess)
            if not ok:
                return None

    return sorted
