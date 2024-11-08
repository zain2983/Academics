import socket
import threading
sepr = "======================================================="

def load_voters(filename):
    voters = {}
    with open(filename, 'r') as file:
        for line in file:
            name, cnic = line.strip().split('/')
            voters[cnic] = name
    return voters

def load_candidates(filename):
    candidates = {}
    with open(filename, 'r') as file:
        for line in file:
            name, symbol = line.strip().split(',')
            candidates[symbol] = name
    return candidates

# Function to handle each client connection
def handle_client(conn, addr, voters, candidates):
    print(f"[NEW CONNECTION] {addr} connected.")
    
    conn.send("Enter your Name: ".encode())
    name = conn.recv(1024).decode().strip()
    conn.send("Enter your CNIC: ".encode())
    cnic = conn.recv(1024).decode().strip()

    if cnic in voters and voters[cnic] == name:
        msg1 = "Authentication successful. Welcome, voter!\nPlease press the enter key to proceed\n"
        conn.send(msg1.encode())

        candidates_list = "\n".join([f"{name} - {symbol}" for symbol, name in candidates.items()])
        msg2 = sepr + f"\nCandidates List:\n{candidates_list}\n"
        conn.send(msg2.encode())
        
        msg3 = sepr + "\nEnter the poll symbol of your chosen candidate: "
        conn.send(msg3.encode())
        symbol = conn.recv(1024).decode().strip()

        while True:
            symbol = conn.recv(1024).decode().strip()
            
            if symbol.lower() == "exit":
                conn.send("Voting process canceled.\n".encode())
                return  # Exit the function to cancel the voting process
            
            if symbol in candidates:
                # Record the vote
                with open("Output.txt", 'a') as file:
                    file.write(f"{sepr}\nName : {name}\nCNIC : {cnic}\nVoted for {symbol}\n")
                msg4 = f"{sepr}\nVote recorded for {candidates[symbol]}.\n{sepr}\nPlease press the enter key to continue\n"
                conn.send(msg4.encode())
                break
            else:
                conn.send("Invalid symbol. Please enter a valid poll symbol (or type 'exit' to cancel): ".encode())
                

    else:
        conn.send("Authentication failed. You are not allowed to vote.\n".encode())
    
    conn.close()

def start_server():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(("localhost", 5555))
    server.listen()
    print("[SERVER STARTED] Waiting for connections...")

    voters = load_voters("Voters_List.txt")
    candidates = load_candidates("Candidates_List.txt")

    while True:
        conn, addr = server.accept()
        thread = threading.Thread(target=handle_client, args=(conn, addr, voters, candidates))
        thread.start()
        print(f"No. of active connections(threads): {threading.active_count() - 1}")

if __name__ == "__main__":
    start_server()

