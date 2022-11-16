#ifndef KERNEL_PCB_H
#define KERNEL_PCB_H
#include <stdint.h>

#define MAX_STACK 1024

// extern queue* PCBqueue;
// extern int currPID;

//PCB structs
//===========================================================================
typedef struct ProcessControlBlock_struct PCB;
struct ProcessControlBlock_struct
{
    uint32_t* ESP; //could need to be not a pointer
    int PID;
}__attribute__((packed));

//queue structs
//===========================================================================
typedef struct queue_node_struct queueNode;
struct queue_node_struct
{
    PCB data;
    queueNode* next;
}__attribute__((packed));

typedef struct queue_struct queue;
struct queue_struct
{
    queueNode* head;
    queueNode* tail;
}__attribute__((packed));


//PCB function prototypes
//===========================================================================
uint32_t* allocStack();
PCB* allocPCB(int PID, uint32_t* ESP);
int create_process(uint32_t processEntry);

//Queue function prototypes
//===========================================================================
void initqueue(queue* qPtr);
queueNode* makeNode(PCB* PCBptr);
void enqueue(queue* qPtr, queueNode* nodePtr);
PCB* dequeue(queue* qPtr);
void currProDeq(queue* qPtr);
void currProEnq(queue* qPtr);

void dispatch();
void dispatch_leave();
void go();

#endif