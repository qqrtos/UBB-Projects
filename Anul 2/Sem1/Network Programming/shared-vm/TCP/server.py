import socket
import json


def number_of_vowels(word):
    nrVowels = 0
    for letter in word:
        if letter in ['a', 'e', 'i', 'o', 'u']:
            nrVowels += 1
    return nrVowels


sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(('0.0.0.0', 6767))
sock.listen(2)

acceptedConnectionSocket, address = sock.accept()

# TEST
# content = acceptedConnectionSocket.recv(128)
# print(content)
# acceptedConnectionSocket.send("Ceaw".encode())

# Pb 1.3
# content = acceptedConnectionSocket.recv(128).decode()
# print("Server side received: " + content)
# acceptedConnectionSocket.send(str(number_of_vowels(content)).encode())

# Pb 3.9
content = acceptedConnectionSocket.recv(128).decode()
print("Server side received: " + content)
numbersDict = json.loads(content)
n1 = int(numbersDict["n1"])
n2 = int(numbersDict["n2"])
acceptedConnectionSocket.send(str(max(n1, n2)).encode())

acceptedConnectionSocket.close()
