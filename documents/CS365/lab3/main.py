#!/usr/bin/python3
from Process import Process
#from MLSQF import MLSQF
from SJF import SJF
import getopt
import sys

words = []
# processes = list()
# processesSJF = list()

options = getopt.getopt(sys.argv[1:], 'v:s:r:c:A:N:S:0:1:2:3:4:5:6:7')
#check option arguments
time_slice = [1, 2, 4, 8, 16, 32, 64, 128]
for opt, arg in options:
    if opt in ('-v', '--verbose'):
        verbose = True
    elif opt in ('-s'):
        seed = int(arg)
    elif opt in ('-r'):
        io_request_chance = int(arg)
    elif opt in ('-c'):
        io_completed_chance = int(arg)
    elif opt in ('-A'):
        scheduling_algorithm = 'MLAS'
    elif opt in ('-N'):
        scheduling_algorithm = 'MLNAS'
    elif opt in ('-S'):
        scheduling_algorithm = 'SJF'
    #get time slice argument
    elif opt in ('-0'):
        time_slice[0] = (int(arg))
    elif opt in ('-1'):
        time_slice[1] = (int(arg))
    elif opt in ('-2'):
        time_slice[2] = (int(arg))
    elif opt in ('-3'):
        time_slice[3] = (int(arg))
    elif opt in ('-4'):
        time_slice[4] = (int(arg))
    elif opt in ('-5'):
        time_slice[5] = (int(arg))
    elif opt in ('-6'):
        time_slice[6] = (int(arg))
    elif opt in ('-7'):
        time_slice[7] = (int(arg))

#open process input file
with open('process', 'r') as file:
    for line in file:
        words.append(line.split(":"))

def menu():
    #z = int(input('(1-4):'))
    #multi level aggressive scheduling
    if scheduling_algorithm == 'SJF':
       sjf = SJF(words, seed, io_request_chance, io_completed_chance)
       sjf.run()
    # elif scheduling_algorithm == 'MLAS':
    #     pr = MulitlevedFeedbackQueue(words, queue_list)
    #     pr.run()
    #multi level non-aggressive scheduling
    # elif scheduling_algorithm == 'MLNAS':
    #     pr = MulitlevedFeedbackQueue(words,
    #                time_slice,
    #                seed,
    #                io_request_chance,
    #                io_completed_chance,
    #                scheduling_algorithm)
    #     pr.run()
    #Preemtive shortest job first
    else:
        print("Wrong input")
        menu()

while(True):
    menu()
