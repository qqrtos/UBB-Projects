# from texttable import Texttable
#
#
# class Plm:
#     def add(self, a, b):
#         return a + b
#
#
# t = Texttable()
# t.add_row([1, 2, 3, 4])
# # print(t.draw())


# a = lambda x: [x+1]
# b = a(1)
# c = lambda x: x + b
# d = c([1])
# a = 1
# b = 3
# print (a, b, c(4), d[1])

def nrEven(li):
    length = len(li)
    if length == 1 and li[0] % 2 == 0:
        return 1
    elif length == 1:
        return 0
    return nrEven(li[:length // 2]) + nrEven(li[length // 2:])


a = [1, 3, 4, 6, 7, 8, 9]
print(nrEven(a))
