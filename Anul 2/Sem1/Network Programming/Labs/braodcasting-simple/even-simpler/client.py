import socket
import random
import threading
import time


def broadcast_recv(client_socket):
    while True:
        msg = client_socket.recv(256)
        print("Received from: " + msg.decode())


client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # UDP
client_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
client_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
client_socket.bind(("", 37020))

client_recv_thread = threading.Thread(args=(client_socket,), target=broadcast_recv)
client_recv_thread.start()

while True:
    msg = str(random.random())
    client_socket.sendto(msg.encode(), ('127.0.0.1', 44444))
    time.sleep(0.75)