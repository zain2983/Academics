import socket
import os

def start_server(host='127.0.0.1', port=65432):
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen()

    print(f"Server listening on {host}:{port}")

    while True:
        conn, addr = server_socket.accept()
        print(f"Connected by {addr}")
        try:
            file_name = conn.recv(1024).decode()
            if os.path.exists(file_name):
                with open(file_name, 'rb') as file:
                    while chunk := file.read(1024):
                        conn.sendall(chunk)
                print(f"Sent file: {file_name}")
            else:
                error_message = "File not found."
                conn.sendall(error_message.encode())
                print(error_message)
        finally:
            conn.close()

if __name__ == "__main__":
    start_server()

