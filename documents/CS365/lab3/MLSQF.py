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

class MLSQF():
    def __init__(self, words, q_first):
        self.p_list = []
        self.queue_list = []
        self.process_queue = words
        self.burst_queue = []
        self.amount = len(words)
        self.create_processes(self.process_queue)
        self.q_first=q_first
    def create_processes(self, p):
        p.sort(key=lambda words: words[2])
        for x in p:
            temp_process = Process(x[0], x[1], x[2], x[3])
            self.p_list.append(temp_process)
            self.queue_list.append(Queue(temp_process))
        self.sort_processes()
    def sort_processes(self):
        temp_queue = []
        temp_queue.append(self.p_list[0])

        for i in range(1, len(self.p_list)):
            temp = []
            for j in range(1, len(self.p_list)):
                if self.p_list[j].arrival_time <= (temp_queue[i-1].burst_time + temp_queue[i-1].arrival_time):
                    temp.append(self.p_list[j])

            temp.sort(key=lambda p_queue: p_queue.priority)
            for x in temp:
                if not x in temp_queue:
                    temp_queue.append(x)

        self.p_list = temp_queue
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