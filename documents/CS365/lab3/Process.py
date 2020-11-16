import random

class Process:
    def __init__(self, p_pid, a_t, b_t, p_p, ts):
        self.pid = int(p_pid)
        self.arrival_time = int(a_t)
        self.burst_time = int(b_t)
        self.priority = int(p_p)
        self.left_burst_time = int(b_t) #Remaining time for service
        self.cycling_time = 0 #Turnaround time
        self.s_time = 0 #start time
        self.e_time = 0 #end time
        self.state = 'nothing' # init state process
        self.current_time_slice = 0
        self.time_slice = int(ts)

    def arrival(self):
        return int(self.arrival_time)

    def burst(self):
        return int(self.burst_time)

    def get_pid(self):
        return str(self.pid)

    def io_request(self, seed, io_rq):
        random.seed(seed)
        if random.randint(0,io_rq) == 1:
            return 1
        return 0

    def io_completed(self, seed, io_cl):
        random.seed(seed)
        if random.randint(0,io_cl) == 1:
            return 1
        return 0

    def time_slice(self):
        return int(self.time_slice)

    def print(self, tick, p_list_rq_io):
        is_io_request = 'false'
        if self.state == 'sleeping':
            is_io_request = 'true'
        if not p_list_rq_io:
            p_list = 'none'
        else:
            p_list = p_list_rq_io
        print("{}:{}:{}:{}:{}:{}".format(tick, self.pid, self.left_burst_time, is_io_request, p_list, self.state))
        #print(tick, self.pid, self.left_burst_time, is_io_request, p_list, self.state)
