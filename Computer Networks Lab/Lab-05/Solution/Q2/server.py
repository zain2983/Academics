import socket

def func1(input_string):
    # Define vowels
    vowels = "aeiouAEIOU"
    
    # Split the input string into words
    words = input_string.split()
    
    # Invert words that contain at least one vowel or keep them as is
    result_words = []
    for word in words:
        if any(vowel in word for vowel in vowels):
            result_words.append(word[::-1])
        else:
            result_words.append(word)
    
    # Join the processed words back into a string
    result = ' '.join(result_words)
    
    return result

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
                inverted_string = func1(client_message)

                print(f"=====================================================\nReceived Message from Client: {client_message}")
                print(f"Inverted String : {inverted_string}")
                
            except socket.error as err:
                print(f"Receive Failed. Error: {err}")
                break

            # Send a response back to the client
            try:
                x = inverted_string
                client_socket.send(x.encode())
            except socket.error as err:
                print(f"Send Failed. Error: {err}")
                break

        # Close the client socket
        client_socket.close()
        print("Client connection closed.")

if __name__ == "__main__":
    main()
