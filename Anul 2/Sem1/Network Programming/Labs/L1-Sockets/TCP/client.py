import socket
import json

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# sock.connect(('127.0.0.1', 6767)) #Windows
sock.connect(('192.168.0.162', 6767))

# TEST
# sock.send("BunA".encode())
# print(sock.recv(128))

# Pb 1.3
# word = input("Send a word: ")
# sock.send(word.encode())
# print("Number of vowels: " + sock.recv(128).decode())

# Pb 3.9
number1 = input("Number 1: ")
number2 = input("Number 2: ")

numbersDict = {"n1": number1, "n2": number2}
sock.send(json.dumps(numbersDict).encode())
print("Biggest number: " + sock.recv(128).decode())

sock.close()
