import socket

def func2(sentence):
    vowels = "aeiouAEIOU"
    
    # Function to check if a word has no vowels
    def has_no_vowels(word):
        return all(char not in vowels for char in word)
    
    # Split the sentence into words
    words = sentence.split()
    
    # Process each word
    inverted_sentence = []
    for word in words:
        if has_no_vowels(word):
            # Invert the word if it has no vowels
            inverted_sentence.append(word[::-1])
        else:
            # Otherwise, keep the word as it is
            inverted_sentence.append(word)
    
    # Join the words back into a sentence
    return " ".join(inverted_sentence)

    
def main():
    # Define server address and port
    server_ip = '127.0.0.1'
    server_port = 2000

    # Create TCP socket
    try:
        tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        print("Socket Created")
    except socket.error as err:
        print(f"Could not create socket. Error: {err}")
        return

    # Connect to the server
    try:
        tcp_socket.connect((server_ip, server_port))
        print("Connected to server")
    except socket.error as err:
        print(f"Connection Failed. Error: {err}")
        return

    # Get input from user
    client_message = input("Enter Message: ")

    # Send the message to the server
    try:
        tcp_socket.send(client_message.encode())
    except socket.error as err:
        print(f"Send Failed. Error: {err}")
        return

    # Receive the response from the server
    try:
        response_message = tcp_socket.recv(1024).decode()
        # print(f"Server Response: {response_message}")
    except socket.error as err:
        print(f"Receive Failed. Error: {err}")
        
    inv_msg = func2(response_message)
    client_message = inv_msg
    print(f"Modified String : {client_message}") 


        
    # Close the socket
    tcp_socket.close()

if __name__ == "__main__":
    main()

