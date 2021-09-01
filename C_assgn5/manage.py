#!/usr/bin/env python3
# import os
# import sys
import socket
import select
import queue
import math

HOST = '127.0.0.1'
PORT = 12345

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as serverSocket:
    serverSocket.bind((HOST, PORT))
    serverSocket.listen(10)

    # Sockets from which we expect to read
    inputs = [ serverSocket ]

    # Sockets to which we expect to write
    outputs = [ ]
    range_num = 0
    current_computes = 0
    results = [ ]
    message_queues = {}

    while inputs:
        # Wait for at least one of the sockets to be ready for processing
        recv_trigg, send_trigg, exceptional = select.select(inputs, outputs, inputs)

        # read message
        for s in recv_trigg:
            if s is serverSocket:
                # accept new connection
                conn, client_addr = s.accept()
                print('connection from ', client_addr)
                conn.setblocking(0)
                inputs.append(conn)
                message_queues[conn] = queue.Queue()
            else:
                data = s.recv(1024)
                if data:
                    # A client socket has data
                    print('received "%s" from %s' % (data, s.getpeername()))
                    if data.decode('UTF-8').strip().find('compute') != -1:
                        #data from compute processes
                        print("compute process: \n", data)
                        # get FLOPS
                        FLOPS = int(data[7:])
                        current_computes += 1
                        #send number range to client to check
                        transfer_msg = 'compute'+str(range_num+1)+'.'
                        new_range = int(math.sqrt(FLOPS*15))
                        divide = 1
                        if range_num > 0:
                            divide = 1 + new_range/range_num
                            divide *= divide
                        range_num += int(new_range/divide)
                        transfer_msg += str(range_num)
                        message_queues[s].put(transfer_msg.encode())
                        if s not in outputs:
                            outputs.append(s)
                    elif data.decode('UTF-8').strip().find('end') != -1:
                        current_computes -= 1
                    elif data.decode('UTF-8').strip().find(',') != -1:
                        #add perfect number to result
                        start_index = 0
                        end_index = 0
                        for i in range(len(data)):
                            if data[i] == 44: # , character
                                start_index = i+1
                            if data[i] == 46: # . character
                                end_index = i
                                results.append(int(data[start_index:end_index]))

                    elif data.decode('UTF-8').strip().find('reportshutdown') != -1:
                        #data from report processes
                        print("report process: ", data)
                        if data.decode('UTF-8').strip().find('shutdown') != -1:
                            # request shutdown
                            for aQueue in message_queues:
                                #send shutdown to compute processes
                                if aQueue != s:
                                    print("send req shut ", aQueue.getpeername())
                                    sendmsg = 'shutdown'
                                    message_queues[aQueue].put(sendmsg.encode())
                                    if aQueue not in outputs:
                                        outputs.append(aQueue)
                    elif data.decode('UTF-8').strip().find('reportreq') != -1:
                        # request report data
                        sendmsg = "computeprocesses:"
                        sendmsg += str(current_computes) + "."
                        sendmsg += " range:"
                        sendmsg += str(range_num) + "."
                        sendmsg += " perfect:"
                        for i in results:
                            sendmsg += str(i)+"|"
                        message_queues[s].put(sendmsg.encode())
                        if s not in outputs:
                            outputs.append(s)

                else:
                    # Interpret empty result as closed connection
                    print('closing ', client_addr)
                    # Stop listening for input on the connection
                    if s in outputs:
                        outputs.remove(s)
                    inputs.remove(s)
                    s.close()

                    # Remove message queue
                    #del message_queues[s]

        # Send message
        for s in send_trigg:
            try:
                next_msg = message_queues[s].get_nowait()
            except queue.Empty:
                outputs.remove(s)
            else:
                s.send(next_msg)

        # Handle exceptional conditions, remove connection
        for s in exceptional:
            # Stop listening
            inputs.remove(s)
            if s in outputs:
                outputs.remove(s)
            s.close()
            # Remove message queue
            del message_queues[s]
