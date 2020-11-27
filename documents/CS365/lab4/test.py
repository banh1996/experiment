#!/usr/bin/python3

import getopt, sys
import random
from time import sleep
import threading
import time
import datetime

# input
g_number_worker = 2
g_mean_arrival_customer_time = 20
g_mean_service_time = 10
g_length_of_time_run = 300

#global variable
g_customer_index = 0
g_current_time_run = 0
# g_customer_queue = []
g_sem = threading.Semaphore(g_number_worker)

#output

def customer_process(service_time):
    global g_customer_index
    # global g_customer_queue

    g_customer_index += 1
    # g_customer_queue.append(g_customer_index)
    current_customer = g_customer_index

    # get data and time arrive
    arrival_time = datetime.datetime.now().time()
    #print("At time", arrival_date, "customer", g_customer_index, "arrives in line")
    print("At time {} customer {} arrives in line".format(arrival_time, current_customer))

    # waiting semaphore
    g_sem.acquire()
    serve_time = datetime.datetime.now()
    print("At time {} customer {} starts being served".format(serve_time, current_customer))

    # sleep service time
    sleep(random.randint(service_time-5, service_time+5))

    # leave cart food, release semaphore
    g_sem.release()
    leave_time = datetime.datetime.now()
    print("At time {} customer {} leaves the food cart".format(leave_time, current_customer))

    # decrease customer
    # g_customer_queue.pop(0)

def generate_customer(mean_time):
    global g_current_time_run
    while (g_current_time_run < g_length_of_time_run):
        temp_time = random.randint(mean_time-10, mean_time+10)
        sleep(temp_time/10)
        g_current_time_run += temp_time

        # create customer process
        if g_current_time_run < g_length_of_time_run:
            # print("create customer in time", temp_time)
            customer_t = threading.Thread(target=customer_process, args=(g_mean_service_time, ))
            customer_t.start()

    print("Close food cart but still serve the remaining customers")

def main():
    gen_cus_t = threading.Thread(target=generate_customer, args=(g_mean_arrival_customer_time, ))
    gen_cus_t.start()

    # while g_customer_queue:
    # for i in range(10):
    #     t = threading.Thread(target=customer_process, name='thread_'+str(i), args=(s, pool))
    #     t.start()

    gen_cus_t.join()

if __name__ == "__main__":
    main()
