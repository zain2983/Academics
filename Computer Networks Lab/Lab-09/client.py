import socket

def start_client():
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect(("localhost", 5555))

    while True:
        message = client.recv(1024).decode()
        if not message:
            break
        print(message, end="")  

        response = input() + '\n'
        client.send(response.encode())

    client.close()

if __name__ == "__main__":
    start_client()

