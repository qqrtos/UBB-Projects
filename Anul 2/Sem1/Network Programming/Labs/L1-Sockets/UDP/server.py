import socket
# import json


def number_of_vocals(word):
    count = 0
    for character in word:
        if character in ['a', 'e', 'i', 'o', 'u']:
            count += 1
    return count


def concat(word1, word2):
    return word1 + word2


def sum_of_digits(number):
    if number != 0:
        return (number % 10) + sum_of_digits(number // 10)
    else:
        return 0


serversocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
serversocket.bind(("0.0.0.0", 6767))

# PB 1.3
# buff, addr = serversocket.recvfrom(512)
# print("Hi, IP " + str(addr[0]) + " and port " + str(addr[1]) + "!")
# print("Received this: " + buff.decode())
#
# print("Sending some stuff over.")
# serversocket.sendto(str(number_of_vocals(buff.decode())).encode(), addr)

# PB 2.1
# buff, addr = serversocket.recvfrom(512)
# buff = json.loads(buff.decode())
#
# print("Received from client: ", end="")
# print(buff)
#
# serversocket.sendto(concat(buff['word1'], buff['word2']).encode(), addr)

# PB 4.1
buff, addr = serversocket.recvfrom(512)
buff = buff.decode()
print("Received this: " + buff + " from port " + str(addr[1]))

serversocket.sendto(str(sum_of_digits(int(addr[1]))).encode(), addr)
