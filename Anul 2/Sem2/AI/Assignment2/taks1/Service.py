from queue import PriorityQueue


class Node:
    def __init__(self, position: (), parent: ()):
        self.position = position
        self.parent = parent
        self.costToStart = 0
        self.costToGoal = 0
        self.totalCost = 0

    def __eq__(self, other):
        return self.position == other.position

    def __lt__(self, other):
        return self.totalCost < other.totalCost


def manhattanDistance(p1, p2):
    return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])


def createPath(endNode, startNode):
    path = []
    while endNode != startNode:
        path.append(endNode.position)
        endNode = endNode.parent
    return path


def searchAStar(mapM, initialX, initialY, finalX, finalY):
    # TO DO
    # implement the search function and put it in controller
    # returns a list of moves as a list of pairs [x,y]

    def shouldAddNode(visited, node):
        for each in visited.keys():
            if each == node and node.totalCost >= each.totalCost:
                return False
        return True

    goalNode = Node((finalX, finalY), None)
    startNode = Node((initialX, initialY), None)

    q = PriorityQueue()
    q.put(startNode)
    visited = {}

    while not q.empty():
        current = q.get()
        visited[current.position] = True

        if current == goalNode:
            return createPath(current, startNode)

        (x, y) = current.position
        neighbors = [(x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1)]

        for neighbor in neighbors:
            if neighbor[0] < 0 or neighbor[0] > 19 or neighbor[1] < 0 or neighbor[1] > 19:
                continue
            if mapM.surface[neighbor[0]][neighbor[1]] != 0:
                continue

            next = Node(neighbor, current)

            if visited.get(next.position) is not None:
                continue

            next.costToStart = manhattanDistance(next.position, startNode.position)
            next.costToGoal = manhattanDistance(next.position, goalNode.position)
            next.totalCost = current.totalCost + next.costToStart + next.costToGoal

            if shouldAddNode(visited, next.position):
                q.put(next)

    return [startNode.position]


def searchGreedy(mapM, initialX, initialY, finalX, finalY):
    # TO DO
    # implement the search function and put it in controller
    # returns a list of moves as a list of pairs [x,y]

    def shouldAddNode(visited, node):
        for each in visited.keys():
            if each == node and node.totalCost >= each.totalCost:
                return False
        return True

    goalNode = Node((finalX, finalY), None)
    startNode = Node((initialX, initialY), None)

    q = PriorityQueue()
    q.put(startNode)
    visited = {}

    while not q.empty():
        current = q.get()
        visited[current.position] = True

        if current == goalNode:
            return createPath(current, startNode)

        (x, y) = current.position
        neighbors = [(x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1)]

        for neighbor in neighbors:
            if neighbor[0] < 0 or neighbor[0] > 19 or neighbor[1] < 0 or neighbor[1] > 19:
                continue
            if mapM.surface[neighbor[0]][neighbor[1]] != 0:
                continue

            next = Node(neighbor, current)

            if visited.get(next.position) is not None:
                continue

            next.costToStart = manhattanDistance(next.position, startNode.position)
            next.costToGoal = manhattanDistance(next.position, goalNode.position)
            next.totalCost = next.costToStart + next.costToGoal

            if shouldAddNode(visited, next.position):
                q.put(next)

    return [startNode.position]


def dummySearch():
    # example of some path in test1.map from [5,7] to [7,11]
    return [[5, 7], [5, 8], [5, 9], [5, 10], [5, 11], [6, 11], [7, 11]]
