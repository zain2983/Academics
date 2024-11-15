import socket
import threading

# Define the maximum number of concurrent clients
MAX_CLIENTS = 3
active_clients = 0  # Keep track of active connections
lock = threading.Lock()  # Protect shared resources

def handle_client(client_socket):
    global active_clients

    try:
        while True:
            # Receive data from the client
            message = client_socket.recv(1024).decode("utf-8")
            
            # Check if the client wants to disconnect
            if message == "DISCONNECT":
                print("Client disconnected")
                break
            
            # Echo the message back to the client
            client_socket.send(message.encode("utf-8"))
    except ConnectionResetError:
        print("Client connection lost unexpectedly.")
    finally:
        # Clean up the connection
        client_socket.close()
        with lock:
            active_clients -= 1
            print(f"Active clients: {active_clients}")

def main():
    global active_clients

    # Create and configure the TCP socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(("0.0.0.0", 5555))
    server_socket.listen()
    print("Server started, waiting for clients...")

    while True:
        client_socket, client_address = server_socket.accept()

        with lock:
            if active_clients >= MAX_CLIENTS:
                # Reject the connection and notify the client
                client_socket.send("Server Full".encode("utf-8"))
                client_socket.close()
                print(f"Rejected connection from {client_address}. Server full.")
            else:
                # Accept the connection and increment active_clients
                active_clients += 1
                print(f"Connected to {client_address}. Active clients: {active_clients}")
                
                # Start a new thread to handle the client
                client_thread = threading.Thread(target=handle_client, args=(client_socket,))
                client_thread.start()

if __name__ == "__main__":
    main()

