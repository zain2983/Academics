import socket

def main():
    # Define server address and port
    server_ip = '127.0.0.1'
    server_port = 2000  # Define the server port

    # Create TCP socket
    try:
        tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        tcp_socket.bind((server_ip, server_port))
        tcp_socket.listen(1)  # Listen for incoming connections
        print("Server is listening for connections...\n")
    except socket.error as err:
        print(f"Could not create or bind socket. Error: {err}")
        return

    while True:  # Run the server in an infinite loop
        # Accept a client connection
        client_socket, client_address = tcp_socket.accept()
        print(f"Connection established with {client_address[0]} on port {client_address[1]}")

        while True:  # Handle the client connection in an inner loop
            # Receive message from the client
            try:
                client_message = client_socket.recv(1024).decode()
                if not client_message:  # Client has disconnected
                    break
                
                # Extract the last element from the received message
                last_element = client_message.split()[-1]  # Split by whitespace and get the last element
                print(f"=====================================================\nHello I am client and my id is {last_element}")
                print(f"Received Message from Client: {client_message}")
                print(f"=====================================================")

            except socket.error as err:
                print(f"Receive Failed. Error: {err}")
                break

            # Send a response back to the client
            try:
                response_message = f"Hello I am server. Your received ID is {last_element}"  # Respond with the last element
                client_socket.send(response_message.encode())
            except socket.error as err:
                print(f"Send Failed. Error: {err}")
                break

        # Close the client socket
        client_socket.close()
        print("Client connection closed.")

if __name__ == "__main__":
    main()
