with open("d_quite_big.in") as file:
    firstLine = [int(_) for _ in file.readline().split(' ')]
    maxSlices = firstLine[0]
    pizzas = file.readline().split(' ')

best = 0
sums = {0}

for pizza in pizzas:
    newSlices = []
    for s in sums:
        ndSum = s + int(pizza)

        if ndSum not in newSlices and ndSum <= maxSlices:
            newSlices.append(ndSum)
            if ndSum >= best:
                best = ndSum

    if len(newSlices) > 3000:
        newSlices.sort()
        newSlices = set(newSlices[:1000])
    else:
        newSlices = set(newSlices)

    sums = sums.union(newSlices)

print(best)
