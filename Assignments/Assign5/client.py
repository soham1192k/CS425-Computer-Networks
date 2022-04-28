import socket,sys,select

max_size = 2048

dead_message = "!quit\n"

client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

if len(sys.argv) != 3:
    print("Correct Usage: script, <IP>, <PORT>")
    exit() 

serverHost = str(sys.argv[1])

serverPort = int(sys.argv[2])

ADDR = (serverHost,serverPort)
client.connect(ADDR)

while True:
    read_sockets,write_socket,error_socket = select.select([sys.stdin,client],[],[])
    for socket in read_sockets:
        if socket == client:
            message = socket.recv(max_size).decode()
            if message:
                print(message)
            else:
                print("Connection closed by server")
                sys.exit()
        else:
            message = sys.stdin.readline()
            client.send(message.encode())
            if message == dead_message:
                client.close()
                sys.exit()