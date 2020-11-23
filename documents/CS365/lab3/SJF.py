from time import sleep
from Process import Process

class SJF:
    def __init__(self, p_list, seed, io_request_chance, io_completed_chance):
        self.processes_list = []
        self.process_queue = p_list
        self.seed = seed
        self.io_request_chance = io_request_chance
        self.io_completed_chance = io_completed_chance
        self.create_processes(self.process_queue)
        self.job_remain = len(self.processes_list)
        self.io_processes_list = []

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
            p_index = self.choose_job(tick)

            #print("choose ", self.job_remain, self.processes_list[p_index].left_burst_time)
            while 1:
                self.add_new_jobs(tick)
                sleep(1)
                for p in self.processes_list:
                    if p.state == 'sleeping': # check if any processes are handling IO
                        if p.io_completed(self.seed, self.io_completed_chance):
                            #print("remove io list ", p.pid)
                            p.state = 'ready'
                            self.io_processes_list.remove(p.pid)

                if p_index == -1:
                    if not self.io_processes_list:
                        temp_list = 'none'
                    else:
                        temp_list = self.io_processes_list
                    print("{}:{}:{}:{}:{}:{}".format(tick, '*', 'x', 'false', temp_list, 'idling'))
                    tick += 1
                    break

                if self.processes_list[p_index].left_burst_time == 1: # if finish work
                    self.processes_list[p_index].state = '* exited'
                    self.job_remain -= 1
                else: # if not finish work
                    if self.processes_list[p_index].io_request(self.seed, self.io_request_chance) and p.state != 'sleeping':
                        self.io_processes_list.append(self.processes_list[p_index].pid)
                        self.processes_list[p_index].state = 'sleeping'
                    else:
                        self.processes_list[p_index].state = 'still running'

                #update process status
                self.processes_list[p_index].left_burst_time -= 1
                if p_index != self.choose_job(tick+1) and self.processes_list[p_index].state != 'sleeping' and self.processes_list[p_index].state != '* exited':# check preemted
                    self.processes_list[p_index].state = 'preemted'
                self.processes_list[p_index].print(tick, self.io_processes_list)
                tick += 1

                if p_index != self.choose_job(tick): #if change job
                    break

    def add_new_jobs(self, tick):
        for p in self.processes_list:
            if tick >= p.arrival_time and p.left_burst_time > 0 and p.state != 'sleeping':
                p.state = 'ready'

    def choose_job(self, tick):
        lowest_burst_time = 9999
        index_process = -1
        index = 0
        for p in self.processes_list:
            if tick >= p.arrival_time and p.left_burst_time > 0 and p.state != 'sleeping' and lowest_burst_time > p.left_burst_time:
                lowest_burst_time = p.left_burst_time
                index_process = index
            index += 1

        return index_process
