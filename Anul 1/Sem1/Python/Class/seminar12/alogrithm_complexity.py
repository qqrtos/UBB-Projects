n = 2
s = 0
for i in range(n ** 2):
    j = i
    while j != 0:
        s += j
        j -= 1
# j depends on i which depends on n
# complexity: T(n)= 1+2+...+n^2 = (n^2(n^2+1))/2   =>   O(n^4)
# n1=10 => 1 sec
# n2=20 => 16 sec
# double input => ratio(n2,n1) = 2/1 => time = O(2^4) = 16

''' SORTING   ALGORITHMS '''
import random

data = list(range(10))
random.shuffle(data)  # randomize elements order
print(data)


# Insertion sort (same array)
def InsertSort(data):
    # Complexity analysis: T(n) =
    for i in range(1, len(data)):  # data[0:i] is already sorted
        currentElement = data[i]
        # figure out where to move this element
        j = i - 1
        while j >= 0 and data[j] > currentElement:
            data[j + 1] = data[j]
            j -= 1
        # insert the element into the list
        data[j + 1] = currentElement
    return data


def merge(data1, data2):
    '''
    Merge 2 lists (== interclasare)
    '''
    pass


# Merge sort - shit sort
def MergeSort(data):
    '''
    Divide the list into halves
    Sort the halves
    Merge the two halves
    '''
    middle = len(data) // 2
    left = MergeSort(data[:middle])
    right = MergeSort(data[middle:])
    return merge(right, left)


print(InsertSort(data))
random.shuffle(data)
print(MergeSort(data))
