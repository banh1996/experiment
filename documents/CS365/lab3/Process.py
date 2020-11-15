import random

class Process:
    def __init__(self, p_pid, a_t, b_t, p_p):
        self.pid = p_pid
        self.arrival_time = a_t
        self.burst_time = b_t
        self.priority = p_p
        self.left_burst_time = b_t #Remaining time for service
        self.cycling_time = 0 #Turnaround time
        self.w_cycling_time = 0 #With right turnaround time
        self.s_time = 0 #start time
        self.e_time = 0 #end time
        self.state = 'sleeping'

    def arrival(self):
        return int(self.arrival_time)

    def burst(self):
        return int(self.burst_time)

    def get_pid(self):
        return str(self.pid)

    def io_request(self, seed, io_rq):
        random.seed(seed)
        if random.randint(0,io_rq) == 0:
            return 1
        return 0

    def io_completed(self, seed, io_cl):
        random.seed(seed)
        if random.randint(0,io_cl) == 0:
            return 1
        return 0

    def print(self, tick, p_list_rq_io):
        is_io_request = 'false'
        if self.state == 'io_wait':
            is_io_request = 'true'
        print("{}:{}:{}:{}:{}:{}:{}".format(tick, self.pid, self.left_burst_time, is_io_request, p_list_rq_io, self.state))
