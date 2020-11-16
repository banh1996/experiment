#!/usr/bin/python3
from Process import Process
from MLFQS import MLFQS
from SJF import SJF
import getopt, sys

words = []
scheduling_algorithm = 'MLAS'
seed = 1
io_request_chance = 10
io_completed_chance = 4
time_slice = [1, 2, 4, 8, 16, 32, 64, 128]
input_file = []
# processes = list()
# processesSJF = list()

options, args = getopt.getopt(sys.argv[1:], 's:r:c:0:1:2:3:4:5:6:7:vANS', ['s=', 
                                                                        'r=',
                                                                        'c=',
                                                                        '0=',
                                                                        '1=',
                                                                        '2=',
                                                                        '3=',
                                                                        '4=',
                                                                        '5=',
                                                                        '6=',
                                                                        '7=',
                                                                        'verbose',
                                                                        'A',
                                                                        'N',
                                                                        'S'])
#check option arguments
for opt, arg in options:
    if opt == '-v':
        verbose = True
    elif opt == '-s':
        seed = int(arg)
    elif opt == '-r':
        io_request_chance = int(arg)
    elif opt == '-c':
        io_completed_chance = int(arg)
    elif opt == '-A':
        scheduling_algorithm = 'MLFQS aggr'
    elif opt == '-N':
        scheduling_algorithm = 'MLFQS non-aggr'
    elif opt == '-S':
        scheduling_algorithm = 'SJF'
    #get time slice argument
    elif opt == '-0':
        time_slice[0] = int(arg)
    elif opt == '-1':
        time_slice[1] = int(arg)
    elif opt == '-2':
        time_slice[2] = int(arg)
    elif opt == '-3':
        time_slice[3] = int(arg)
    elif opt == '-4':
        time_slice[4] = int(arg)
    elif opt == '-5':
        time_slice[5] = int(arg)
    elif opt == '-6':
        time_slice[6] = int(arg)
    elif opt == '-7':
        time_slice[7] = int(arg)

input_file = sys.argv[len(sys.argv) - 1]

#open process input file
with open(input_file, 'r') as file:
    for line in file:
        words.append(line.split(":"))

if scheduling_algorithm == 'SJF':
    #print("run SJF")
    sjf = SJF(words, seed, io_request_chance, io_completed_chance)
    sjf.run()
elif scheduling_algorithm == 'MLFQS non-aggr':
    print("run MLFQS non-aggr")
    ml = MLFQS(words, seed, io_request_chance, io_completed_chance, time_slice)
    ml.run()
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
