#!/usr/bin/python3
import sys
import random
from time import sleep
import threading
from threading import Lock
import datetime

# input
g_worker_number = int(sys.argv[1])
g_mean_arrival_customer_time = int(sys.argv[2])
g_mean_service_time = int(sys.argv[3])
g_length_of_time_run = int(sys.argv[4])

# global variable
g_start_time = 0
g_sem = threading.Semaphore(g_worker_number) #Customer waits in semaphore queue
# there are only 2 global variables that need to be protected between threads.
g_mutex_customer_index = Lock() #prevent to not access global variable g_customer_index at the same time
g_mutex_waiting_time = Lock() #prevent to not access global variable g_total_waiting_time at the same time
g_customer_index = 0
g_total_waiting_time = 0

def customer_process(service_mean_time, deviation_time):
    global g_sem
    global g_mutex_customer_index
    global g_mutex_waiting_time
    global g_customer_index
    global g_start_time
    global g_total_waiting_time

    g_mutex_customer_index.acquire()
    g_customer_index += 1
    current_customer = g_customer_index
    g_mutex_customer_index.release()

    # get data and time arrive
    arrival_time = datetime.datetime.now() - g_start_time
    print("At time {} customer {} arrives in line".format(round(arrival_time.total_seconds()*10), current_customer))

    # waiting semaphore
    g_sem.acquire()
    serve_time = datetime.datetime.now() - g_start_time
    g_mutex_waiting_time.acquire()
    g_total_waiting_time += (serve_time.total_seconds() - arrival_time.total_seconds())*10
    g_mutex_waiting_time.release()
    print("At time {} customer {} starts being served".format(round(serve_time.total_seconds()*10), current_customer))

    # sleep service time
    sleep(random.randint(service_mean_time-deviation_time, service_mean_time+deviation_time)/10)

    # Customer leaves food cart, release semaphore
    leave_time = datetime.datetime.now() - g_start_time
    print("At time {} customer {} leaves the food cart".format(round(leave_time.total_seconds()*10), current_customer))
    g_sem.release()

def generate_customer(worker_number, mean_arrival_time, deviation_time):
    global g_customer_index
    global g_sem
    global g_start_time
    global g_total_waiting_time
    g_start_time = datetime.datetime.now()
    current_time_run = datetime.datetime.now() - g_start_time
    while (current_time_run.total_seconds()*10 < g_length_of_time_run):
        sleep(random.randint(mean_arrival_time-deviation_time, mean_arrival_time+deviation_time)/10)
        current_time_run = (datetime.datetime.now() - g_start_time)

        # create customer process
        if current_time_run.total_seconds()*10 < g_length_of_time_run:
            customer_t = threading.Thread(target=customer_process, args=(g_mean_service_time, deviation_time))
            customer_t.start()

    # print("Close food cart but still serve the remaining customers")
    while g_sem._value != worker_number:
        1
    print("Simulation terminated after {} customers served".format(g_customer_index))
    print("Average waiting time =", g_total_waiting_time/g_customer_index)

def main():
    global g_worker_number
    global g_mean_arrival_customer_time
    global g_mean_service_time
    global g_length_of_time_run
    print("Number of tellers:", g_worker_number)
    print("Mean inter-arrival time:", g_mean_arrival_customer_time)
    print("Mean service time:", g_mean_service_time)
    print("Length of simulation:", g_length_of_time_run)
    # select deviation_time to random delay
    deviation_time = round(min(g_mean_arrival_customer_time, g_mean_service_time)/3)
    gen_cus_t = threading.Thread(target=generate_customer, args=(g_worker_number, g_mean_arrival_customer_time, deviation_time))
    gen_cus_t.start()
    gen_cus_t.join()

if __name__ == "__main__":
    main()
