from Process import Process

class Queue:
    def __init__(self, process_list):
        self.process_list=process_list
        self.level=process_list.priority
        self.q=0

    def size(self):
        return len(self.process_list)

    def get(self,index):
        return self.process_list[index]    

    def add(self,process):
        self.process_list.append(process)

    def delete(self,index):
        self.process_list.remove(self.process_list[index])