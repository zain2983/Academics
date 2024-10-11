import socket

def download_file(host='127.0.0.1', port=65432, file_name=''):
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((host, port))

    client_socket.sendall(file_name.encode())
    with open(file_name, 'wb') as file:
        while True:
            chunk = client_socket.recv(1024)
            if not chunk:
                break
            file.write(chunk)
            print(chunk.decode())
    # print(f"Downloaded file: {file_name}")
    client_socket.close()

if __name__ == "__main__":
    file_to_download = input("Enter the file name to download: ")
    download_file(file_name=file_to_download)



