#!/usr/bin/python3
from Process import Process
from FCFS import FCFS
from SJF import SJF
from Priority import Priority
from PSJF import PSJF
import logging
import argparse

words = []
processes = list()
processesSJF = list()

#check verbose is enable
parser = argparse.ArgumentParser()
parser.add_argument("-v", "--verbose", help="increase output verbosity",
                    action="store_true")
args = parser.parse_args()
if args.verbose:
    logging.basicConfig(level=logging.DEBUG)
logging.debug('enable verbose')

#open process input file
with open('process', 'r') as file:
    for line in file:
        words.append(line.split())

def menu():
    print("\nWhat algorithm you want to launch?")
    print('1. FCFS')
    print('2. SJF')
    print('3. Priority')
    print('4. Preemptive shortest job first')
    print('5. End')
    z = int(input('(1-4):'))
    if z == 1:
        fcfs = FCFS(words)
        fcfs.run()
    elif z == 2:
        sjf = SJF(words)
        sjf.run()
    elif z == 3:
        pr = Priority(words)
        pr.run()
    elif z == 4:
        pr = PSJF(words)
        pr.run()
    elif z == 45:
        pass
    else:
        print("Wrong input")
        menu()

while(True):
    menu()
