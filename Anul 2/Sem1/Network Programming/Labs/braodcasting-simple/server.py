import socket
import threading
import time


def serve_client(client_socket, broadcast_socket, broadcast_port):
    while True:
        msg = client_socket.recv(18)
        print(msg.decode())
        broadcast_send(broadcast_socket, broadcast_port, msg.decode())


def broadcast_send(broadcast_socket, port, message):
    # while True:
    broadcast_socket.sendto(message.encode(), ('<broadcast>', port))
    # time.sleep(0.75)


if __name__ == "__main__":
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    # server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
    server_socket.bind(('', 6767))
    server_socket.listen(5)

    broadcast_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    broadcast_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

    # broadcast_thread = threading.Thread(args=(broadcast_socket, 8000), target=broadcast_send)
    # broadcast_thread.start()

    while True:
        client_socket, client_address = server_socket.accept()
        threading.Thread(args=(client_socket, broadcast_socket, 8000), target=serve_client).start()
