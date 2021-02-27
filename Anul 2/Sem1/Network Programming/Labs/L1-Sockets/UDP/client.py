import socket
# import json

mysocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# PB 1.3
# mysocket.sendto(b"cuvantul", ("127.0.0.1", 6767))
# print("Sent stuff to the server.")
#
# print("Received this from the server: ", end="")
# print(mysocket.recvfrom(512))

# PB 2.1
# mysocket.sendto(json.dumps({'word1': "bunica", 'word2': "bunicul"}).encode(), ("127.0.0.1", 6767))
# print("Sent JSON to the server")
#
# buff, addr = mysocket.recvfrom(512)
# print("Received: " + buff.decode() + " from IP " + str(addr[0]))

# PB 4.1
message = input("What should we send to the server? ")
mysocket.sendto(message.encode(), ("127.0.0.1", 6767))
print("Message sent.")

buff, addr = mysocket.recvfrom(512)
print("Received back: " + buff.decode())
