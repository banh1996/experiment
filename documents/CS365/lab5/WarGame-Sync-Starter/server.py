#!/usr/bin/python3
import asyncio
from collections import namedtuple
from enum import Enum
import logging
import random
import socket
import socketserver
import threading
import sys
from program import Command
from program import Result

class ClientContext:
    def __init__(self):
        self.deck = []
    def init_deck(self):
        for i in range (0, 52):
            self.deck.append(i)
    def draw_client_deck(self, deck):
        client_deck = []
        for i in range(0, 26):
            card = random.choice(deck)
            client_deck.append(card)
            deck.remove(card)
        return client_deck
    async def handle_client(self, reader, writer):
        data = await reader.readexactly(3)
        message = data.decode()
        addr = writer.get_extra_info('peername')

        print(f"Received {message!r} from {addr!r}")

        #print(f"Send: {message!r}")
        #writer.write(data)
        client_deck = self.draw_client_deck(self.deck)
        send_data = bytearray()
        send_data.append(28)
        send_data.append(Command.WANTGAME.value)
        for i in range(0, len(client_deck)):    
            send_data.append(client_deck[i])
        #writer.write(bytes([send_data]))
        writer.write(send_data)
        await writer.drain()

        print("Close the connection")
        writer.close()

async def server(host, port, loop):
    try:
        client = ClientContext()
        client.init_deck()
        server = await asyncio.start_server(client.handle_client, host, port)
        addr = server.sockets[0].getsockname()
        print(f'Serving on {addr}')
        async with server:
            await server.serve_forever()
        return 1
    except ConnectionResetError:
        logging.error("ConnectionResetError")
        return 0
    except asyncio.streams.IncompleteReadError:
        logging.error("asyncio.streams.IncompleteReadError")
        return 0
    except OSError:
        logging.error("OSError")
        return 0

def main(args):
    host = args[0]
    port = int(args[1])

    loop = asyncio.get_event_loop()
    loop.run_until_complete(server(host, port, loop))
    loop.close()

if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    main(sys.argv[1:])
