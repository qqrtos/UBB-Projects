import socket


def broadcast_send(broadcast_socket, port, message):
    broadcast_socket.sendto(message.encode(), ('<broadcast>', port))


server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
# server_socket.settimeout(0.2)
server_socket.bind(("", 44444))

while True:
    msg = server_socket.recv(256)
    print("Received: " + msg.decode())
    broadcast_send(server_socket, 37020, msg.decode())
