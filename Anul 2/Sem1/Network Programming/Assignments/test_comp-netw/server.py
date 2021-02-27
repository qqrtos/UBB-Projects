import socket
import threading

connected_clients = []


def serve_client(client_socket, client_addr, broadcast_socket, broadcast_port):
    while True:
        try:
            msg = client_socket.recv(128)
            if msg.decode() == "quit":
                disconnect_client(client_socket, client_addr, broadcast_socket, broadcast_port)
                break
            else:
                broadcast_send_message(broadcast_socket, broadcast_port, msg.decode())
        except:
            print("Connection abruptly closed.")
            break


def disconnect_client(client_socket, client_addr, broadcast_socket, broadcast_port):
    connected_clients.remove((client_socket, client_addr))
    broadcast_send_message(broadcast_socket, broadcast_port, "Client " + str(client_addr) + " disconnected.")
    client_socket.shutdown(socket.SHUT_RDWR)
    client_socket.close()
    # broadcast_send_arr(broadcast_socket, broadcast_port)


def broadcast_send_message(broadcast_socket, broadcast_port, message):
    broadcast_socket.sendto(message.encode(), ('<broadcast>', broadcast_port))


def broadcast_send_arr(broadcast_socket, port):
    # TODO: send array using this function instead of sending messages each time someone (dis)connects
    broadcast_socket.sendto(len(connected_clients).to_bytes(4, byteorder='little'), ('<broadcast>', port))
    for (clientaddr, clientsocket) in connected_clients:
        broadcast_socket.sendto(str(clientaddr).encode(), ('<broadcast>', port))


if __name__ == "__main__":
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('', 7000))
    server_socket.listen(5)

    broadcast_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    broadcast_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

    while True:
        client_socket, client_addr = server_socket.accept()
        connected_clients.append((client_socket, client_addr))
        broadcast_send_message(broadcast_socket, 8000, "Client " + str(client_addr) + " connected.")
        # broadcast_send_arr(broadcast_socket, 8000, connected_clients)

        threading.Thread(args=(client_socket, client_addr, broadcast_socket, 8000), target=serve_client).start()
