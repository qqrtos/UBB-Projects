data = [6, -2, -3, 1, 5, -2, -1, 2, -9]


def maxSum(arr):
    # global -> best I've seen so far
    # local -> best right now
    global_sum = arr[0]

    # for i in range(len(data)):
    #     for j in range(i, len(arr)):
    #         local_sum = sum(arr[i:j])
    #         if local_sum>global_sum:
    #             global_sum=local_sum

    for i in range(len(data)):
        local_sum = arr[i]
        if local_sum > global_sum:
            global_sum = local_sum
        for j in range(i + 1, len(arr)):
            local_sum += arr[j]
            if local_sum > global_sum:
                global_sum = local_sum

    return global_sum


def divideConquerMiddle(arr, low, high):
    middle = (low + high) // 2
    # for loop with partial sums between low and middle
    # for loop with partial sums between middle and high
    # add max partial sum in left half to right half with arr[m] and return it
    pass


def divideConquerMax(arr, low, high):
    if low == high:
        return arr[0]

    middle = (low + high) // 2
    return max(divideConquerMax(arr, middle + 1, high), divideConquerMax(arr, low, middle),
               divideConquerMiddle(arr, low, high))


def dynamicSum(arr):
    global_sum = arr[0]
    local_sum = arr[0]

    for i in range(1, len(arr)):
        local_sum = max(arr[i], arr[i] + local_sum)
        global_sum = max(global_sum, local_sum)

    return global_sum


print(maxSum(data))
# print(divideConquerMax(data, 0, len(data) - 1))
print(dynamicSum(data))

print("\nDistance between strings")

s1 = 'saturday'
s2 = 'saturnday'


# transform s1 into s2 using minimal operations
# character by character, start from the end
def xform(s1, s2):
    if len(s1) == 0:
        return len(s2)  # transfsorm empty string into s2 -> len(s2) operations
    elif len(s2) == 0:
        return len(s1)  # transform string into empty string
    elif s1[-1] == s2[-1]:
        return xform(s1[:-1], s2[:-1])  # if the last chars are equal, drop them

    return 1 + min(
        xform(s1[:-1], s2),  # delete last char of s1
        xform(s1[:-1], s2[:-1]),  # replace last character
        xform(s1, s2[:-1])  # insert ar the end of s1
    )


print(xform(s1, s2))
