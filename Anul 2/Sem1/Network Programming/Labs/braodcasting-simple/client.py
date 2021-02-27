import socket
import threading


def broadcast_wait(broadcast_socket):
    while True:
        data = broadcast_socket.recv(18)
        print("Received from broadcast: " + data.decode())


client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('127.0.0.1', 6767))

broadcast_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
broadcast_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
broadcast_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
broadcast_socket.bind(('', 8000))

threading.Thread(args=(broadcast_socket,), target=broadcast_wait).start()

while True:
    msg = input("Mesaj: ").encode()
    client_socket.send(msg)
