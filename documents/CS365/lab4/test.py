import getopt, sys
import random
from time import sleep
import threading
import time

# class thread_customer(object):
#     def __init__(self):
#         super(ThreadPool, self).__init__()
#         self.active = []
#         self.lock = threading.Lock()
#     def makeActive(self, name):
#         with self.lock:
#             self.active.append(name)
#             logging.debug('Running: %s', self.active)
#     def makeInactive(self, name):
#         with self.lock:
#             self.active.remove(name)
#             logging.debug('Running: %s', self.active)

# def f(s, pool):
#     logging.debug('Waiting to join the pool')
#     with s:
#         name = threading.currentThread().getName()
#         pool.makeActive(name)
#         time.sleep(0.5)
#         pool.makeInactive(name)

# input
g_number_worker = 10
g_mean_time = 20
g_mean_service_time = 20
g_length_of_time_run = 500

#global variable
g_customer_index = 0
g_current_time_run = 0
g_customer_queue = []
g_sem = threading.Semaphore(g_number_worker)

#output

def generate_customer(mean_time):
    global g_current_time_run
    global g_customer_index
    global g_customer_queue
    while (g_current_time_run < g_length_of_time_run):
        temp_time = random.randint(mean_time-10, mean_time+10)
        print("temp time", temp_time)
        sleep(temp_time/10)
        g_current_time_run += temp_time
        g_customer_index += 1
        g_customer_queue.append(g_customer_index)
    print("end time")

def main():
    gen_cus_t = threading.Thread(target=generate_customer, args=(g_mean_time, ))
    gen_cus_t.start()
    gen_cus_t.join()

    # for i in range(10):
    #     t = threading.Thread(target=f, name='thread_'+str(i), args=(s, pool))
    #     t.start()

if __name__ == "__main__":
    main()