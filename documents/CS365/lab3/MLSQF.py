from Process import Process
from Queue import Queue

class RR:
    def __init__(self,process_list,q):
        self.process_list=process_list
        self.q=q
    def scheduling(self):
        process_list.sort(key=lambda x:x.arrive_time)#Sort by .arrive_time
        len_queue=len(self.process_list) #The length of the process queue
        index=int(0)  #index
        q=self.q      # 
        running_time=int(0)#Already running time

        #Scheduled loop
        while(True):
            #Current Process
            current_process=self.process_list[index%len_queue]
            #Judge whether the current process has been completed
            if current_process.left_serve_time>0: 
                #Calculate completion time
                #The service time is greater than or equal to the time slice, then the completion time + time slice time This process has not ended
                #If the service time is less than the time slice, the completion time will be added to the original time to continue the service
                if current_process.left_serve_time>=q:
                    running_time+=q
                    #print(current_process.name,running_time,index)
                    current_process.left_serve_time-=q

                else :
                    #print('%s still needs service time less than the current time slice'%current_process.name)
                    running_time+=current_process.left_serve_time
                    current_process.left_serve_time=0


            #completed
            if current_process.left_serve_time==0:
                #Calculate completion time
                current_process.finish_time=running_time
                #Calculate turnaround time
                current_process.cycling_time=current_process.finish_time-current_process.arrive_time
                #Calculate weighted turnaround time
                current_process.w_cycling_time=float(current_process.cycling_time)/current_process.serve_time
                #print
                print('%s process has completed the process, the details are as follows:'%current_process.name)
                print('Process name: %s, completion time: %d, turnaround time: %d, weighted turnaround time: %.2f'%(current_process.name,current_process.finish_time,current_process.cycling_time,current_process.w_cycling_time))
                #pop up
                self.process_list.remove(current_process)
                len_queue=len(self.process_list)
                #After a process completes the task, the index is first rolled back and then added to keep pointing to the next process that needs to be scheduled
                index-=1
            #indexRegular increase
            index+=1     

            #If there is no process in the queue, the execution is complete
            if len(self.process_list)==0:
                break

            #Change index, to avoid errors when taking modulo because index is greater than len
            if index>=len(self.process_list):
                index=index%len_queue

class MLSQF:
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
            self.processes_list.append(Process(x[0], x[1], x[2], x[3]))

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
                        self.processes_list[p_index].is_handle_io = True # change state process to sleep
                        self.processes_list[p_index].state = 'sleeping'
                    else:
                        self.processes_list[p_index].state = 'still running'

                #calculate
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

    def scheduling(self):
        q_list=self.queue_list  #Current queue collection
        q_first=self.q_first    #The time slice of the first queue

        for i in range(len(q_list)):
            #Determine the time slice of each queue
            if i==0:
                q_list[i].q=q_first
            else :
                q_list[i].q=q_list[i-1].q*2

            #Execute the time slice from the first queue
            #First determine whether it is the last queue, the last queue directly executes the RR scheduling algorithm
            #If it is not the last queue, it will judge whether it is necessary to join the end of the next queue after executing the current queue time slice
            if i==len(q_list)-1:
                #print(q_list[i].process_list[])
                #Reset the arrival time of the last queue
                for t in range(len(q_list[i].process_list)):
                    q_list[i].process_list[t].arrive_time=t
                rr_last_queue=RR(q_list[i].process_list,q_list[i].q)
                rr_last_queue.scheduling()
            else:
                currentQueue=q_list[i]

                index=int(0)
                while(True):
                    if currentQueue.get(index).left_serve_time>q_list[i].q:
                        currentQueue.get(index).left_serve_time-=q_list[i].q
                        print('Number %d queue time slice: %d'%(i,q_list[i].q))
                        print('The process has not been executed, it needs to be added to the end of the next queue: process name: %s'%(currentQueue.get(index).name))
                        #Throw the current process to the end of the next queue
                        q_list[i+1].add(currentQueue.get(index))
                        index+=1  
                    else:
                        print('Service complete and pop up:',currentQueue.get(index).name)
                        currentQueue.get(index).left_serve_time=0
                        currentQueue.delete(index)

                    if index==currentQueue.size():
                        break
