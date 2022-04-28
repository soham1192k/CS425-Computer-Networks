from ntpath import join
from socket import *
from threading import Thread
import sys

addresses = {}
clients = {}

dead_message = "!quit\n"

serverHost = str(sys.argv[1])
serverPort = int(sys.argv[2])
buffSize = 2048

def handle_client(client):
    name = client.recv(buffSize).decode()[:-1]
    welcome_msg="Welcome "+str(name)+"! If you ever want to quit, type !quit to exit the room."
    client.send(welcome_msg.encode())
    joining_msg=str(name)+" has joined the chat."
    broadcast(joining_msg)
    clients[client] = name

    while True:
        message = client.recv(buffSize).decode()
        if message:
            if message != dead_message:
                broadcast(message, name + ": ")
            else:
                client.send(dead_message.encode())
                client.close()
                print(f'Connection from {addresses[client]} is closed')
                del clients[client]
                broadcast(f'{name} has left the chat.')
                break
        else:
            client.close()
            print(f'Connection from {addresses[client]} is closed')
            del clients[client]
            broadcast(f'{name} has left the chat.')
            break
        
def broadcast(message, prefix=''):
    for client in clients:
        client.send((prefix + message).encode())

if __name__ == "__main__":
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)
    serverSocket.bind((serverHost, serverPort))
    serverSocket.listen()
    print('The server is ready to receive. Waiting for connection...')
    while True:
        clientSocket, clientAddr = serverSocket.accept()
        print(f'Connection from {clientAddr} is established')
        clientSocket.send('Welcome to the chat room! Enter your name.'.encode())
        addresses[clientSocket] = clientAddr
        Thread(target=handle_client, args=(clientSocket,)).start()
    serverSocket.close()