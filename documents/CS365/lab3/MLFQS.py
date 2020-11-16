from Process import Process
from Queue_Process import Queue_Process
from time import sleep

class MLFQS:
    def __init__(self, p_list, seed, io_request_chance, io_completed_chance, time_slice):
        self.processes_list = []
        self.time_slice = []
        self.process_queue = p_list
        self.seed = seed
        self.io_request_chance = io_request_chance
        self.io_completed_chance = io_completed_chance
        self.time_slice = time_slice
        self.create_processes(self.process_queue)
        self.job_remain = len(self.processes_list)
        self.io_processes_list = []
        self.queues = []
        for i in range(8):
            self.queues.append([])

    def create_processes(self, p):
        #sort arrival time
        p.sort(key=lambda words: words[2])
        for x in p:
            self.processes_list.append(Process(x[0], x[1], x[2], x[3], 0))

    def run(self):
        tick = 0
        #add new jobs to ready run
        self.add_new_jobs(tick)
        self.job_remain = len(self.processes_list)
        while self.job_remain != 0:
            # choose job
            p = self.choose_job()

            #print("choose ", self.job_remain, p.left_burst_time)
            while 1:
                self.add_new_jobs(tick)
                sleep(1)
                for temp_p in self.processes_list:
                    if temp_p.state == 'sleeping': # check if any processes are handling IO
                        if temp_p.io_completed(self.seed, self.io_completed_chance):
                            #print("remove io list ", p.pid)
                            temp_p.state = 'ready'
                            self.io_processes_list.remove(temp_p.pid)

                if p == -1:
                    if not self.io_processes_list:
                        temp_list = 'none'
                    else:
                        temp_list = self.io_processes_list
                    print("{}:{}:{}:{}:{}:{}".format(tick, '*', 'x', 'false', temp_list, 'idling'))
                    tick += 1
                    break

                if p.left_burst_time == 1: # if finish work
                    p.state = '* exited'
                    self.job_remain -= 1
                    self.remove_queue(p)
                else: # if not finish work
                    if p.io_request(self.seed, self.io_request_chance) and p.state != 'sleeping':
                        p.state = 'sleeping'
                    elif p.time_slice > p.current_time_slice:
                        p.state = 'still running'
                    # else: #use up time slice
                    #     p.priority += 1
                    #     self.re_enqueue(p)
                    #     p.state = 'preemted'

                # if p != self.choose_job(tick+1) and p.state != 'sleeping' and p.state != '* exited':# check preemted
                #     p.state = 'preemted'
                if p.time_slice <= p.current_time_slice and p.state != 'sleeping' and p.state != '* exited':
                    p.priority += 1
                    self.re_enqueue(p)
                    p.state = 'preemted'
                #update process status
                p.left_burst_time -= 1
                p.current_time_slice += 1
                p.print(tick, self.io_processes_list)
                tick += 1

                # if p != self.choose_job(tick): #if change job
                #     break

    def add_new_jobs(self, tick):
        for p in self.processes_list:
            if tick >= p.arrival_time and p.left_burst_time > 0 and p.state != 'sleeping' and p.state != 'ready' and p.state != 'still running':
                p.state = 'ready'
                # ready start burst, set priority = 0, push to queue 0
                p.priority = 0
                # print("enque", p.pid)
                self.queues[0].append(p)

    def choose_job(self):
        for i in range(8):
            for p in self.queues[i]:
                # assign time slice
                # print("choo", p.pid)
                p.time_slice = self.time_slice[i]
                p.current_time_slice = 0
                return p
        return -1

    def re_enqueue(self, process):
        for i in range(8):
            for p in self.queues[i]:
                if p.pid == process.pid:
                    # print("re queue ", p.pid)
                    self.queues[i].remove(p)
                    if i != 7:
                        # add queue to tail
                        # print("add queue ", p.pid)
                        self.queues[i+1].append(p)
                    return

    def remove_queue(self, process):
        for i in range(8):
            for p in self.queues[i]:
                if p.pid == process.pid:
                    # print("remove p list ", p.pid)
                    self.queues[i].remove(p)
                    return
