"""
 Author: Kevin Allen
 CS372 Project 
 Description: Implements the chatserve portion of the project
    Socket setup taken from class notes
"""
from socket import *
import sys

#sets up socket connect, takes a port number as a string and returns the serverSocket
def setup(str):
    serverPort = int(float(str)) #convert from string to an integer
    serverSocket = socket(AF_INET, SOCK_STREAM)
    serverSocket.bind(('', serverPort))
    serverSocket.listen(1)
    return serverSocket

def recieve():
    message = connectionSocket.recv(2048).decode();
    print(message)

def respond():
    response = raw_input('HAL> ')   #server name is HAL
    if response == "\quit":
        connectionSocket.close()
    response = 'HAL>' +response + '\n'       #add server id and newline to response before sending back
    connectionSocket.send(response.encode())

serverSocket = setup(sys.argv[1])
while 1:
    connectionSocket, addr = serverSocket.accept();
    while 1:
        recieve()
        respond()
