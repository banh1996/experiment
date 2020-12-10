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
        self.total_deck = []
        self.ready_new_game = [asyncio.Event()]*2048
        self.compare_event = [asyncio.Event()]*2048
        self.cards_compare = [100]*2048
        self.client_total_num = 0
        self.mutex_client_center = Lock()
    def distribute_deck(self, deck):
        client_deck = []
        for i in range(0, 26):
            card = random.choice(deck)
            client_deck.append(card)
            deck.remove(card)
        return client_deck
    def init_client_decks(self):
        deck = []
        for i in range (0, 52):
            deck.append(i)
        deck1 = self.distribute_deck(deck)
        self.total_deck.append(deck)
        self.total_deck.append(deck1)
        #return len(self.total_deck)
    def add_client_num(self):
        self.mutex_client_center.acquire()
        client_num = self.client_total_num
        self.ready_new_game[client_num].clear()
        self.client_total_num += 1
        if self.client_total_num%2 == 0:
            # enough 2 clients, start game
            self.ready_new_game[client_num].set()
            self.ready_new_game[client_num-1].set()
            self.init_client_decks()
        self.mutex_client_center.release()
        return client_num
    def compare_card(self, client1_card, client2_card):
        # compare card rank, rank 1-13 is 2,3,...Q,K,ACE
        client1_card_rank = client1_card%13
        if client1_card_rank == 0:
            client1_card_rank = 13
        client2_card_rank = client2_card%13
        if client2_card_rank == 0:
            client2_card_rank = 13
        if client1_card_rank > client2_card_rank:
            return Result.WIN.value
        elif client1_card_rank == client2_card_rank:
            return Result.DRAW.value
        else:
            return Result.LOSE.value
    async def get_server_result(self, card, client_num):
        self.cards_compare[client_num] = card
        if client_num%2 == 1:
            other_client_num = client_num - 1
        else:
            other_client_num = client_num + 1

        if self.compare_event[other_client_num].is_set() == False:
            self.compare_event[client_num].set()
            self.compare_event[other_client_num].clear()
            # must wait another client card to compare
            await self.compare_event[other_client_num].wait()
            #logging.info(f"wait in client {client_num}")
        self.compare_event[other_client_num].set()
        result = self.compare_card(self.cards_compare[client_num], self.cards_compare[other_client_num])
        logging.info(f"client {client_num} cal result {self.cards_compare[client_num]} and {self.cards_compare[other_client_num]}")

        self.compare_event[client_num].clear()
        #self.compare_event[other_client_num].clear()
        #if client_num%2 == 0:
        if self.compare_event[other_client_num].is_set() == True:
            self.cards_compare[client_num] = 100
            self.cards_compare[other_client_num] = 100
        return result

    async def handle_client(self, reader, writer):
        data = await reader.readexactly(3)
        message = data.decode()
        addr = writer.get_extra_info('peername')
        logging.info(f"Received {message!r} from {addr!r}")

        if data[2] != Command.WANTGAME.value:
            #logging.info(f"{client_num} quit game")
            #self.quit_game()
            return
        client_num = self.add_client_num()
        # wait another client
        logging.info(f"added client {client_num} ")
        await self.ready_new_game[client_num].wait()

        # get distributed cards, a couple client decks is the first&second in total_deck
        client_deck = self.total_deck[client_num]
        #send_data = bytearray()
        send_data = b""
        send_data += b'\27'
        send_data += bytes(int(Command.GAMESTART.value).to_bytes(1, "big"))

        for i in range(0, len(client_deck)):    
            send_data += bytes(int(client_deck[i]).to_bytes(1, "big"))
        #writer.write(bytes([send_data]))
        logging.info(f"client {client_num} cards {send_data}")
        writer.write(send_data)

        #read card
        for i in range (0, 26):
            data = await reader.readexactly(3)
            # self.compare_event[client_num].clear()
            logging.info(f"Client {client_num} Index {i} Received {data[2]}")
            result = await self.get_server_result(data[2], client_num)
            # logging.info(f"Client {client_num} Index {i} Received {data[2]} Result {result}")
            writer.write(bytes([2, Command.PLAYRESULT.value, result]))

        data = await reader.readexactly(3)

        await writer.drain()
        logging.info("Quit game")
        writer.close()

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
