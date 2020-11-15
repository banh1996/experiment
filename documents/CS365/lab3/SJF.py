from tqdm import tnrange, tqdm_notebook, tqdm
from time import sleep
from Process import Process

class SJF:
    def __init__(self, p_list, seed, io_request_chance, io_completed_chance):
        self.processes_list = []
        self.process_queue = p_list
        self.burst_queue = []
        self.amount = len(p_list)
        self.seed = seed
        self.io_request_chance = io_request_chance
        self.io_completed_chance = io_completed_chance
        self.create_processes(self.process_queue)
        self.fill_queue()

    def create_processes(self, p):
        #sort start time
        p.sort(key=lambda words: words[2])

        for x in p:
            self.processes_list.append(Process(x[0], x[1], x[2], x[3]))

        self.sort_processes()

    def sort_processes(self):
        temp_queue = []
        temp_queue.append(self.processes_list[0])

        for i in range(1, len(self.processes_list)):
            temp = []
            for j in range(1, len(self.processes_list)):
                if self.processes_list[j].arrival_time <= (temp_queue[i-1].burst_time + temp_queue[i-1].arrival_time):
                    temp.append(self.processes_list[j])

            temp.sort(key=lambda p_queue: p_queue.burst_time)
            for x in temp:
                if not x in temp_queue:
                    temp_queue.append(x)

        self.processes_list = temp_queue

    def fill_queue(self):
        for p in self.processes_list:
            self.burst_queue.append(p.burst())

        print ('ProcessID\tArrivalTime\tBurstTime')
        for x in self.processes_list:
            print (x.pid, '\t\t', x.arrival_time, '\t\t', x.burst_time)
        sleep(1)

    def run(self):
        tick = 0
        job_remain = len(self.processes_list)
        while job_remain == 0:
            p_index = self.choose_job(tick)
            while 1:
                #add job to ready run
                self.calculate()
                self.processes_list[p_index].state = 'still running'
                for p in self.processes_list:
                    if p.state == 'io_wait':
                        if p.io_completed(self.seed, self.io_completed_chance):
                            p.state = 'sleeping'
                    elif p.io_request(self.seed, self.io_request_chance):
                        p.state = 'io_wait'

                if self.processes_list[p_index].left_burst_time == 1:
                    self.processes_list[p_index].state = '*' #exited
                else:
                    if self.processes_list[p_index].io_request(self.seed, self.io_request_chance):
                        self.processes_list[p_index].state = 'io_wait'
                tick += 1
                self.processes_list[p_index].print('none')


        # self.calculate()
        # sleep(1)
        # for x in range(self.amount):
        #     actual_pid = str(self.processes_list[x].pid)
        #     #self.log.start(actual_pid, t-int(self.processes_list[x].arrival_time))
        #     for i2 in tqdm(range(self.burst_queue[x]), desc=actual_pid):
        #         #self.log.pending(actual_pid)
        #         self.processes_list[x].print(t, 11, 12, 'none')
        #         sleep(1)
        #         t += 1
        #         for p in self.processes_list:
        #             if int(p.arrival_time) == int(t) and str(p.pid) != actual_pid:
        #                 tqdm.write('Process {} is waiting. Time: {}'.format(p.pid, t))
                        #self.log.waiting(p.pid)
        #self.log.final(self.average_wait_time, self.amount)

    def calculate(self, index):
        self.processes_list[p_index].left_burst_time -= 1

    def choose_job(self, tick):
        # start_time = 0
        # m = len(self.processes_list)
        # for p in self.processes_list:
        #     if int(p.arrival_time) > start_time:
        #         start_time = p.arrival_time
        #         p.w_cycling_time = 0
        #     else:
        #         p.w_cycling_time = start_time - int(p.arrival_time)
        #     p.e_time = start_time + int(p.burst_time)
        #     start_time += int(p.burst_time)
        lowest_burst_time = 9999
        index_process = 0
        index = 0
        for p in self.processes_list:
            if tick >= p.arrival_time and p.left_burst_time > 0 and lowest_burst_time > p.left_burst_time:
                lowest_burst_time = p.left_burst_time
                index_process = index
            index += 1
        return index_process
