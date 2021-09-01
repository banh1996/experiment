#!/usr/bin/env python3
import os
import socket
import sys

#input
is_shutdown = 0
if len(sys.argv) > 1:
    if sys.argv[1] == "-k":
        is_shutdown = 1

shutdown_msg = 'reportshutdown'
server_address = ('localhost', 12345)

# Create a TCP/IP socket
socks = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect the socket to the port where the server is listening
socks.connect(server_address)

# Send messages on both sockets
if is_shutdown == 1:
    socks.send(shutdown_msg.encode())
else:
    # Read responses on both sockets
    sendmsg = 'reportreq'
    socks.send(sendmsg.encode())
    data = socks.recv(2048)
    print(data)

socks.close()
