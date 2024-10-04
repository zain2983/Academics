import socket

def main():
    # Define server address and port
    server_ip = '127.0.0.1'
    server_port = 2000
    
    # Create UDP socket
    while True:
        try:
            udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            print("Socket Created")
        except socket.error as err:
            print(f"Could not create socket. Error: {err}")
            return

        # Get input from user
        client_message = input("Enter Message (YY-AAAA-CI or YY-AAAA-CO): ")
        
        # Send the message to the server
        try:
            udp_socket.sendto(client_message.encode(), (server_ip, server_port))
        except socket.error as err:
            print(f"Send Failed. Error: {err}")
            return

        # Receive the message back from the server
        try:
            server_message, _ = udp_socket.recvfrom(2000)
            print(f"Server Message: {server_message.decode()}")
        except socket.error as err:
            print(f"Receive Failed. Error: {err}")
            return

        # Close the socket
        udp_socket.close()

if __name__ == "__main__":
    main()
