#!/usr/bin/python3
import asyncio
from collections import namedtuple
from enum import Enum
import logging
import random
import socket
import socketserver
import threading
from threading import Lock
import sys
from program import Command
from program import Result


class ClientContext:
    def __init__(self):
        self.ready_new_game = 0
        self.client_total_num = 0
        self.client_quit_num = 0
        self.mutex_client_center = Lock()
    def get_client_num(self):
        self.mutex_client_center.acquire()
        self.client_total_num += 1
        if self.client_total_num%2 == 1
            self.ready_new_game = 1
        else
            self.ready_new_game = 0
        self.mutex_client_center.release()
    def quit_game(self, client_num):
        self.mutex_client_center.acquire()
        self.client_quit_num += 1
        # if self.client_quit_num%2 == 0
        #     self.ready_new_game = 0
        self.mutex_client_center.release()
        await writer.drain()
        logging.info("Quit game")
        writer.close()
    def init_deck(self, deck):
        for i in range (0, 52):
            deck.append(i)
    def draw_client_deck(self, deck):
        client_deck = []
        for i in range(0, 26):
            card = random.choice(deck)
            client_deck.append(card)
            deck.remove(card)
        return client_deck
    def compare_card(self, client_card, server_deck):
        server_card = random.choice(server_deck)
        server_deck.remove(server_card)
        client_card_rank = client_card%13
        if client_card_rank == 0:
            client_card_rank = 13
        server_card_rank = server_card%13
        if server_card_rank == 0:
            server_card_rank = 13
        if client_card_rank > server_card_rank:
            return Result.WIN.value
        elif client_card_rank == server_card_rank:
            return Result.DRAW.value
        else:
            return Result.LOSE.value
    async def handle_client(self, reader, writer):
        deck = []
        self.init_deck(deck)
        client_num = self.get_client_num()
        data = await reader.readexactly(3)
        # message = data.decode()
        # addr = writer.get_extra_info('peername')
        # logging.info(f"Received {message!r} from {addr!r}")
        # while self.has_opponent:
        #     1
        if data[2] != Command.WANTGAME.value:
            self.quit_game()
            return

        client_deck = self.draw_client_deck(deck)
        #send_data = bytearray()
        send_data = b""
        send_data += b'\27'
        send_data += bytes(int(Command.GAMESTART.value).to_bytes(1, "big"))

        for i in range(0, len(client_deck)):    
            send_data += bytes(int(client_deck[i]).to_bytes(1, "big"))
        #writer.write(bytes([send_data]))
        logging.info(f"len {len(send_data)}")
        writer.write(send_data)

        #read card
        for i in range (0, 26):
            data = await reader.readexactly(3)
            logging.info(f"Index {i} Received {data[2]}")
            result = self.compare_card(data[2], deck)
            writer.write(bytes([2, Command.PLAYRESULT.value, result]))

        data = await reader.readexactly(3)

        self.quit_game()

async def server(host, port, loop):
    try:
        client = ClientContext()
        server = await asyncio.start_server(client.handle_client, host, port)
        addr = server.sockets[0].getsockname()
        logging.info(f'Serving on {addr}')
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
