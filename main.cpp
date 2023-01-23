#include<iostream>
#include<cmath> 
#include<string>
#include<fstream>

#define time int 
using namespace std;

class Scheduler;
class Process_Creater;

class table{
private:
    int Id;
    string *Status=(string *)malloc(sizeof(char)*10);
public:
    void setId(int id){
        Id = id;}
    void setstat(string stat){
        Status = &stat;}

    int getId(){
        return Id;}
    string getstat(){
        return *Status;}
};

class tableNode{
public:
    table node;
    tableNode *next;
    tableNode *previous;

    tableNode(tableNode *nxt = NULL, tableNode *prev = NULL){
        next = (tableNode *)malloc(sizeof(tableNode));
        previous = (tableNode *)malloc(sizeof(tableNode));
        next = nxt;
        previous = prev;
    }
};

class tableList{
private:
    int millisecond;
    int size;
    tableNode *head;
    tableNode *tail;
public:
    tableList(int sec=0){
        size = 0;
        millisecond = sec;
        head = (tableNode *)malloc(sizeof(tableNode));
        tail = (tableNode *)malloc(sizeof(tableNode));
        head = tail = NULL;

    }
    void pushBack(table &nod){
        tableNode *temp = (tableNode *)malloc(sizeof(tableNode));
        temp->node = nod;
        temp->next = NULL;
        if(size == 0){
            temp->previous = NULL;
            head = temp;
            tail = temp;
        }
        else{
            temp->previous = tail;
            tail->next = temp;
            tail = temp;
        }
        size++;
    }
    void pushFront(table &nod){
        tableNode *temp = (tableNode *)malloc(sizeof(tableNode));
        temp->node = nod;
        temp->previous = NULL;
        if(size == 0){
            temp->next = NULL;
            tail = temp;
        }
        else{
            temp->next = head;
            head->previous = temp;
        }
        head = temp;
        size++;
    }
    
    void print(ofstream &print){
        tableNode *temp = head;
        while(temp != NULL){
            print<< millisecond << "\t\t\t\t\t\t" << temp->node.getId() << "\t\t\t\t\t" << temp->node.getstat()<<endl;
            temp = temp->next;
        }
    }

    void setHead(tableNode *H){
        head = H;}
    void setTail(tableNode *T){
        tail = T;}
    void setSecond(int sec){
        millisecond = sec;}
    void resetSize(){
        size = 0;}

    int getSize(){
        return size;}
    tableNode *getHead(){
        return head;}
    tableNode *getTail(){
        return tail;}
    int setSecond(){
        return millisecond;}
};

class Process{
private:
    int pId;
    bool inExecution;
    time arrival;
    time cpuBrust, completion, turnAroundTime, waiting, response, remaining;
    bool IObound;
    time IOstart;
    Process *next, *previous;

public:
    friend class Process_Creater;
    // Constructor with deafult parameter so it work as both a normal and default constructor for process intilization
    Process(int id, time arr=0, time brust = 1, time comp = 1, time tat = 1, time wait = 1, time res = 1, bool io = false, time IOs = -1, int siz= 0, bool exe=false){
        pId = id;
        arrival = arr;
        cpuBrust = brust;
        completion = comp;
        turnAroundTime = tat;
        waiting = wait;
        response = res;
        remaining = brust;
        IObound = io;
        IOstart = IOs;
        inExecution = exe;
    }

    // Some function to set and get value of process data members
    void setid(int id){
        pId = id;}
    void setArrival(time arr){
        arrival = arr;}
    void setcpuBrust(time brust){
        cpuBrust = brust;}
    void setCompletion(time comp){
        completion = comp;}
    void setTurnAroundTime(time tat){
        turnAroundTime = tat;}
    void setWaiting(time wait){
        waiting = wait;}
    void setResponse(time res){
        response = res;}
    void setRemaining(time rem){
        remaining = rem;}
    void setIObound(bool flag){
        IObound = flag;}
    void setIOstart(time t){
        IOstart = t;}
    void setexe(bool flag){
        inExecution = flag;}

    int getId(){
        return this->pId;}
    time getArrival(){
        return arrival;}
    time getcpuBrust(){
        return this->cpuBrust;}
    time getCompletion(){
        return this->completion;}
    time getTurnAroundTime(){
        return this->turnAroundTime;}
    time getWaiting(){
        return this->waiting;}
    time getResponse(){
        return this->response;}
    time getRemaining(){
        return remaining;}
    bool getIObound(){
        return IObound;}
    time getIOstart(){
        return IOstart;}
    bool getexe(){
        return inExecution;}
};

class Process_Creater{
private:
    int size;
    Process **array;
public:
    Process_Creater(int siz = 0, time sl = 1000){
        size = siz;
        array = new class Process * [size];
        srand((unsigned) time(0));
        for(int i=0; i<size; i++){
            Process *p = (Process *)malloc(sizeof(Process));
            p->setid(i +1);
            time temp;
            if(sl == 0)
                temp = 1;
            else
                temp = (rand() % (sl / 10));
            p->setArrival(temp);
            if(sl == 0)
                temp = 1;
            else
                temp = rand() % (sl/20) + 1;
            p->setcpuBrust(temp);
            p->setRemaining(temp);
            temp = rand() % 2;
            p->setIObound((bool)temp);
            p->setexe(true);
            if(temp){
                temp = (rand() % p->getcpuBrust()) + 1;
                p->setIOstart(temp);
            }
            array[i] = p;
            if(i!=0||i!=size-1){
                array[i] = array[i - 1];
                array[i] = array[i + 1];
            }   
        }  
    }
    friend class Scheduler;
    void create(int siz, time sl){
        size = siz;
        array = (Process **)malloc(sizeof(Process*)*size);
        srand((unsigned) time(0));
        for(int i=0; i<size; i++){
            Process *p = (Process *)malloc(sizeof(Process));
            p->setid(i +1);
            time temp;
            if(sl == 10)
                temp = 1;
            else
                temp = (rand() % (sl / 10));
            p->setArrival(temp);
            if(sl == 20)
                temp = 1;
            else
                temp = rand() % (sl/20) + 1;
            p->setcpuBrust(temp);
            p->setRemaining(temp);
            temp = rand() % 2;
            p->setIObound((bool)temp);
            p->setexe(true);;
            if(temp){
                if(p->getcpuBrust() == 0)
                    p->setIOstart(0);
                else{
                    temp = (rand() % (p->getcpuBrust())) + 1;
                    p->setIOstart(temp);
                }
            }
            array[i] = p;
        }
        for (int i = 0; i < size; i++){
            if(i!=0)
                array[i]->previous = array[i - 1];
            if(i!=size-1)
                array[i]->next = array[i + 1];
        }
    }
};

class ReadyQueueNode{
private:
    Process *item;   // Ready Queue Node
    int priority;
    ReadyQueueNode * l, *r;
public:
    ReadyQueueNode(Process *&node, int prior=0){
        item = node;
        priority = prior;
        l = r = NULL;
    }
    Process *getItem(){
        return item;}
    void setPriority(int p){
        priority = p;
    }
    void setItem(Process *temp){
        item = temp;}
    int getPriority(){
        return priority;
    }

    friend class ReadyQueue;
};

class ReadyQueue{   
private:
    int size;
    int capacity;
    ReadyQueueNode **arr;
public:
    // Constructor for heap or ready queue
    ReadyQueue( int capc = 0){
        size = capc;
        capacity = capc;
        arr = new ReadyQueueNode *[capc];
    }

    bool isempty(){
        if(size == 0)
            return false;
        return true;
    }

    // to exchange to node in heap
    void exchange(ReadyQueueNode **a, ReadyQueueNode **b){
        ReadyQueueNode *temp = *a;
        *a = *b;
        *b = temp;
    }

    // function to define algorithms for scheduling
    void heapify(int index){
        int l = 2*index + 1;
        int r = 2*index + 2;
        int smallest = index;

        if((l < size) && (arr[l]->priority < arr[smallest]->priority)){
            smallest = l;
        }
        if((r < size) && (arr[r]->priority < arr[smallest]->priority)){
            smallest = r;
        }

        if (smallest != index) {
            exchange(&arr[smallest],&arr[index]);
            heapify(smallest);
        }
    }

    // function to delete root node
    ReadyQueueNode * deleteMinNode(){
        ReadyQueueNode *temp = arr[0];
        arr[0] = arr[size - 1];
        size--;
        heapify(0);
        return temp;
    }

    // function to insert a node 
    void insertMinHeap( ReadyQueueNode *node){
        if (size + 1 > capacity){
            capacity = capacity * 2;
            ReadyQueueNode **temp = new ReadyQueueNode *[capacity];
            for (int i = 0; i < size; i++)
                temp[i] = arr[i];

            this->arr = temp;
            delete (temp);
        }
        node->l=NULL;
        node->r = NULL;
        size++;
        int i = size - 1;
        while(i && node->priority < arr[(i-1)/2]->priority){
            arr[i] = arr[(i - 1) / 2];
            i = (i - 1) / 2;
        }
        if(arr[2*i + 1]!=NULL)
            node->l = arr[2*i + 1];   
        if(arr[2*i + 2]!=NULL)
            node->r = arr[2*i + 2];   
        arr[i] = node; 
    }
    
    // Create a heap if it is not initilise
    void createHeap(int capc){
        size = 0;
        capacity = capc;
        arr = new ReadyQueueNode *[capc];
    }

    int getsize(){
        return size;}
};

class Scheduler{
private:
    ReadyQueue queue;
    int num_process;
    Process_Creater array;
    tableList **Table;
    string algo;
public:
    Scheduler(int num, time st){
        num_process = num;
        array.create(num, st);
        queue.createHeap(num);
        Table = (tableList **)malloc(sizeof(tableList *)*st);
        for (int i = 0; i < st; i++){
            tableList *temp = (tableList *)malloc(sizeof(tableList));
            temp->setSecond(i);
            temp->setHead(NULL);
            temp->setTail(NULL);
            temp->resetSize();
            Table[i] = temp;
        }
    }

    void start(time quantum, time st, int num, string al){
        algo = al;
        if(algo == "FCFS"){
            FCFS(st);
        }
        else if(algo == "RR"){
            RR(quantum, num, st);
        }
        else
            CFS(st);
    }

    void FCFS(time st){
        int num_completed = 0;
        time i = 0;
        time j = 0;
        int x = 0;
        int inarr = 0;
        while((num_completed != num_process) && j<=st){
            string stat;
            for (int a = 0; a < array.size && inarr != array.size; a++){
                if(array.array[a]->getArrival() <= i && array.array[a]->getexe()){
                    ReadyQueueNode *tempNode = (ReadyQueueNode *)malloc(sizeof(ReadyQueueNode));
                    tempNode->setItem(array.array[a]);
                    tempNode->setPriority(array.array[a]->getArrival());
                    queue.insertMinHeap(tempNode);
                    array.array[a]->setexe(false);
                    inarr++;
                }
            }
            i++;
            if(queue.isempty()){
                num_completed++;
                ReadyQueueNode *temp = queue.deleteMinNode();
                stat = "Arrived";
                Process *item = temp->getItem();
                int arr = item->getArrival();
                table *node0 = (table *)malloc(sizeof(table));
                node0->setId(item->getId());
                node0->setstat(stat);
                Table[arr]->pushBack(*node0);
                x++;
                item->setCompletion(j + item->getcpuBrust());
                item->setWaiting(j - item->getcpuBrust() - arr);
                if (item->getWaiting() < 0)
                    item->setWaiting(0);
                item->setTurnAroundTime(item->getWaiting() + item->getcpuBrust());
                item->setResponse(j - item->getArrival());
                if(item->getResponse() < 0)
                    item->setResponse(0);
                stat = "Running";
                table *node = (table *)malloc(sizeof(table));
                node->setId(item->getId());
                node->setstat(stat);
                Table[j]->pushBack(*node);
                x++;
                stat = "Exit";
                table *node1 = (table *)malloc(sizeof(table));
                node1->setId(item->getId());
                node1->setstat(stat);
                Table[item->getCompletion()]->pushBack(*node1);
                x++;
                j = j + item->getcpuBrust();
                i=j;
            }
            else
                j++;
        }
        ofstream print;
        print.open("status.txt");
        string t = "\t\t\t\t\t";
        print << "Millisecond Number	    Process Id"<<"\t\t\t"<<"Status\n";
        for(int a = 0; a<=i; a++){
            if(Table[a]->getSize() == 0)
                continue;
            Table[a]->print(print);
        }
    }

    void RR(time quantum, int num, int st){
        int num_completed = 0;
        time i =0;
        int j = 0;
        int x = 0;
        int inarr = 0;
        while((num_completed != num_process) && i<=st){
            string stat;
            for (int a = 0; a < array.size && inarr != array.size; a++){
                if(array.array[a]->getArrival() <= i && array.array[a]->getexe()){
                    ReadyQueueNode *tempNode = (ReadyQueueNode *)malloc(sizeof(ReadyQueueNode));
                    tempNode->setItem(array.array[a]);
                    tempNode->setPriority(array.array[a]->getArrival());
                    queue.insertMinHeap(tempNode);
                    array.array[a]->setexe(false);
                    inarr++;
                }
            }
            i++;
            if(queue.isempty()){
                ReadyQueueNode *temp = queue.deleteMinNode();
                Process *item = temp->getItem();
                if(item->getcpuBrust() == item->getRemaining()){
                    stat = "Arrived";
                    table *node0 = (table *)malloc(sizeof(table));
                    node0->setId(item->getId());
                    node0->setstat(stat);
                    item->setResponse(j - item->getArrival());
                    if(item->getResponse() < 0)
                        item->setResponse(0);
                    Table[item->getArrival()]->pushBack(*node0);
                    x++;
                }
                int rem = item->getRemaining();
                stat = "Running";
                table *node = (table *)malloc(sizeof(table));
                node->setId(item->getId());
                node->setstat(stat);
                Table[j]->pushBack(*node);
                x++;
                if((rem - quantum) > 0 )
                    item->setRemaining(rem - quantum);
                else{
                    item->setCompletion(j + rem);
                    item->setRemaining(0);
                    item->setTurnAroundTime(j + rem - item->getArrival()); // tat = exit/completion - arrival
                    item->setWaiting(item->getTurnAroundTime() - item->getcpuBrust());             // waiting = tat - brust
                    if (item->getWaiting() < 0)
                        item->setWaiting(0);
                    stat = "Exit";
                    table *node1 = (table *)malloc(sizeof(table));
                    node1->setId(item->getId());
                    node1->setstat(stat);
                    Table[j + rem]->pushBack(*node1);
                    x++;
                    num_completed++;
                }
                j = j + rem - item->getRemaining();
                i = j;
                if(item->getRemaining()!=0){
                    temp->setPriority(j);
                    queue.insertMinHeap(temp);
                }
            }
            else{  
            j++;
            }
        }
        ofstream print;
        print.open("status.txt");
        string t = "\t\t\t\t\t";
        print << "Millisecond Number	    Process Id"<<"\t\t\t"<<"Status\n";
        for(int a = 0; a<=i; a++){
            if(Table[a]->getSize() == 0)
                continue;
            Table[a]->print(print);
        }
    }

    void CFS(time st){
        int num_completed = 0;
        int clock = 0;
        time clockbrust = 0;
        time latency = 210;
        int inarr = 0;
        int tablecount=0;
        unsigned int vruntime = 0;
        while((num_completed != num_process) && clock<=st){
            string stat;
            for (int i = 0; i < array.size && inarr != array.size; i++){
                if(array.array[i]->getArrival() <= clock && array.array[i]->getexe()){
                    ReadyQueueNode *tempNode = (ReadyQueueNode *)malloc(sizeof(ReadyQueueNode));
                    tempNode->setItem(array.array[i]);
                    tempNode->setPriority(0);
                    queue.insertMinHeap(tempNode);
                    array.array[i]->setexe(false);
                    inarr++;
                }
            }
            clock++;
            if(queue.isempty()){
                ReadyQueueNode *temp = queue.deleteMinNode();
                Process *item = temp->getItem();
                time maxruntime = ceil(float(latency)/(float)queue.getsize());
                if(item->getcpuBrust() == item->getRemaining()){
                    stat = "Arrived";
                    table *node0 = (table *)malloc(sizeof(table));
                    node0->setId(item->getId());
                    node0->setstat(stat);
                    item->setResponse(clockbrust - item->getArrival());
                    if(item->getResponse() < 0)
                        item->setResponse(0);
                    Table[item->getArrival()]->pushBack(*node0);
                    tablecount++;
                }
                
                int rem = item->getRemaining();
                stat = "Running";
                table *node = (table *)malloc(sizeof(table));
                node->setId(item->getId());
                node->setstat(stat);
                Table[clockbrust]->pushBack(*node);
                tablecount++;
                if((rem - maxruntime) > 0 ){
                    if((item->getIObound())&&((item->getcpuBrust()-rem)<=item->getIOstart())&&((item->getIOstart() - item->getcpuBrust() + rem) <= maxruntime)){
                        vruntime = (item->getIOstart() - item->getcpuBrust() + rem);
                        item->setRemaining(rem - vruntime -1);
                    }
                    else{
                        item->setRemaining(rem - maxruntime);
                        vruntime = maxruntime;
                    }
                }
                else{
                    if(item->getIObound()&&(item->getcpuBrust()-rem)<=item->getIOstart()&&(item->getIOstart() - item->getArrival() + rem) <= maxruntime){
                        vruntime = (item->getIOstart() - item->getArrival() + rem);
                        item->setRemaining(rem - vruntime);
                    }
                    item->setCompletion(clockbrust + rem);
                    item->setRemaining(0);
                    item->setTurnAroundTime(clockbrust + rem - item->getArrival()); // tat = exit/completion - arrival
                    item->setWaiting(item->getTurnAroundTime() - item->getcpuBrust());             // waiting = tat - brust
                    if (item->getWaiting() < 0)
                        item->setWaiting(0);
                    stat = "Exit";
                    table *node1 = (table *)malloc(sizeof(table));
                    node1->setId(item->getId());
                    node1->setstat(stat);
                    Table[clockbrust + rem]->pushBack(*node1);
                    vruntime = rem;
                    tablecount++;
                    num_completed++;
                }
                clockbrust = clockbrust + vruntime;
                clock = clockbrust;
                if(item->getRemaining()!=0){
                    temp->setPriority(temp->getPriority() + vruntime);
                    queue.insertMinHeap(temp);
                }
            }
            else
            clockbrust++;
        }
        ofstream print;
        print.open("status.txt");
        string t = "\t\t\t\t\t";
        print << "Millisecond Number	    Process Id"<<"\t\t\t"<<"Status\n";
        for(int i = 0; i<=clock && i<st; i++){
            if(Table[i]->getSize() == 0)
                continue;
            Table[i]->print(print);
        }
    }

    void printProcess(){
        ofstream print;
        print.open("process.txt");
        string t = "\t\t";
        print << "pId\t\tA T\t\tB T\t\tC T\t\tTAT\t\tW T\t\tR T\t\tIObound\n";
        for (int i = 0; i < array.size; i++){
            print << array.array[i]->getId() << t << array.array[i]->getArrival() << t << array.array[i]->getcpuBrust() << t << array.array[i]->getCompletion() << t << array.array[i]->getTurnAroundTime() << t << array.array[i]->getWaiting() << t << array.array[i]->getResponse() <<t<<array.array[i]->getIObound()<<endl;
        }
    }
};

class Simulator{
private:
    string algo;
    time quantum;
    time simulationTime;
    int num_Process;
public:
    Simulator(string &str, time &simTime, time quanta = 0){
        algo = str;
        quantum = quanta;
        simulationTime = simTime;
        srand((unsigned) time(0));
        num_Process = simTime/(rand() % 25);
    }
    
    void start(){
        Scheduler schedule(num_Process, simulationTime);
        schedule.start(quantum, simulationTime, num_Process, algo);
        schedule.printProcess();
    }
};

void welcome(){
    int i = 30;
    while(i--)
        cout << "__";
    i = 30;
    cout << endl;
    while(i--)
        cout << "__";
    cout << endl;
    cout << "\t\t Welcome to Avadhesh Kumar's \n\t    CPU Scheduling Algorithm Simulator" << endl;
    i = 30;
    while(i--)
        cout << "__";
    i = 30;
    cout << endl;
    while(i--)
        cout << "__";
    cout << endl;
}

int main(){
    welcome();
    cout << "\nEnter Simulation time(in milliseconds)\nName of Scheduling algorithm from given:\n\tFirst Come First Serve (FCFS)\n\tRound Robin\n\tCompletely Fair Scheduler (CFS)\nTime quantum in case of Round Robin\n"<< endl;

    time simul=100;
    string algo="CFS";
    time quanta;
    cin >> simul >> algo;
    if(algo == "RR")
        cin >> quanta;
    Simulator simulation( algo, simul, quanta);
    simulation.start();
    return 0;
}