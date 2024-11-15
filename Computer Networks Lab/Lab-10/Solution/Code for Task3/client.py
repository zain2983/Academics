import socket

def main():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(("127.0.0.1", 5555))

    while True:
        # Get input from the user
        message = input("Enter message (or 'DISCONNECT' to exit): ")

        # Send the message to the server
        client_socket.send(message.encode("utf-8"))

        # If the user wants to disconnect, close the socket and break the loop
        if message == "DISCONNECT":
            print("Disconnected from server")
            client_socket.close()
            break

        # Receive and print the response from the server
        response = client_socket.recv(1024).decode("utf-8")
        print("Server response:", response)

if __name__ == "__main__":
    main()

