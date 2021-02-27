import socket
import threading

client_list = []


def broadcast_wait(broadcast_socket):
    while True:
        try:
            data = broadcast_socket.recv(4)
            client_list = []
            length = int.from_bytes(data, byteorder='little')
            while data > 0:
                elem = broadcast_socket.recv(36).decode()
                client_list.append(elem)


        except:
            print("closed")
            break


if __name__ == "__main__":
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('127.0.0.1', 7000))

    broadcast_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    broadcast_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    broadcast_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    broadcast_socket.bind(('', 8000))

    broadcast_thread = threading.Thread(args=(broadcast_socket,), target=broadcast_wait)
    broadcast_thread.start()

    while True:
        msg = input("> ")
        client_socket.send(msg.encode())
        if msg == "quit":
            client_socket.close()
            broadcast_socket.close()
            break
