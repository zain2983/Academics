# -- coding: cp1252 --
import socket

# Database to keep track of checked-in students
attendance_db = []

def main():
    # Define server address and port
    server_ip = '127.0.0.1'
    server_port = 2000

    # Create UDP socket
    try:
        udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        udp_socket.bind((server_ip, server_port))
        print("Socket Created and Bound")
    except socket.error as err:
        print(f"Could not create or bind socket. Error: {err}")
        return

    print("Listening for Messages...\n")

    while True:
        # Receive the message from the client
        try:
            client_message, client_address = udp_socket.recvfrom(2000)
            client_message = client_message.decode()
            print("==========================================================")
            print(f"Received Message from IP: {client_address[0]} and Port No: {client_address[1]}")
            print(f"Client Message: {client_message}")

            # Process the message
            response_message = process_message(client_message)
            udp_socket.sendto(response_message.encode(), client_address)
        except socket.error as err:
            print(f"Receive Failed. Error: {err}")
            return

def process_message(message):
    global attendance_db
    parts = message.split('-')
    
    if len(parts) != 3:
        return "Invalid message format. Use YY-AAAA-CI or YY-AAAA-CO."
    else:
        try:
            if type(int(parts[1])) == int:
                pass
        except ValueError:
            return "Invalid message format. Use YY-AAAA-CI or YY-AAAA-CO."

    roll_number = parts[0] + '-' + parts[1]
    action = parts[2]

    if action == "CI":  
        if roll_number in attendance_db:
            return "You are already here."
        else:
            attendance_db.append(roll_number)
            return f"Welcome Student {roll_number}. Current Attendance: {attendance_db}"

    elif action == "CO":
        if roll_number not in attendance_db:
            return "You didn’t check in today. Contact System Administrator."
        else:
            attendance_db.remove(roll_number)
            return f"Goodbye Student {roll_number}! Have a nice day. Current Attendance: {attendance_db}"

    return "Invalid action. Use CI for check-in or CO for check-out."

if __name__ == "__main__":
    main()
