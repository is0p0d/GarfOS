#include "kernel_pcb.h"
#include "screenutils.h"
#include "buddy.h"
extern int currPID;
extern queue* PCBqueue_ptr;
extern PCB* currProcess;
PCB* allocPCB(int PID, uint32_t* ESP)
{
    PCB* newPCB;
    if((newPCB = (PCB*)kmalloc(sizeof(newPCB))) == NULL)
    {
        err_msg("!ERROR! :: Memory exhaustion in allocPCB");
    }
    else
    {
        newPCB->ESP = ESP;
        newPCB->PID = PID;
    }

    return newPCB;
}
int create_process(uint32_t processEntry)
{   
    uint32_t* stackPtr = (int)kmalloc(MAX_STACK);
    uint32_t ss = 24, cs = 16, ds = 8, es = 8, fs = 8, gs = 8;

    uint32_t* st = stackPtr+1024;
    st--;
    *st = 0x00000200;
    st--;
    *st = cs;
    st--;
    *st = processEntry;
    st--;
    *st = &dispatch_leave;
    for (int i = 0; i < 8; i++)
    {
        st--;
        *st = 0; 
    }

    PCB* tempProcess = allocPCB(currPID++, st);

    enqueue(PCBqueue_ptr, makeNode(tempProcess));
}

void initqueue(queue* qPtr)
{
    qPtr->head = qPtr->tail = NULL; //set the head and tail to null equivalent
}
queueNode* makeNode(PCB* PCBptr)
{
    queueNode* node;
    if((node = (queueNode*)kmalloc(sizeof(queueNode))) == NULL)
        err_msg("!ERROR! :: Memory exhaustion in makeNode");
    else
    {
        node->data = *PCBptr;
        node->next = NULL;
    }
    return node;
}
void enqueue(queue* qPtr, queueNode* nodePtr)
{
    if(nodePtr == (NULL))
        err_msg("!ERROR! :: Attempt to enqueue a null node.");
    else if(qPtr->head == NULL)
    {
        qPtr->head = nodePtr;
        qPtr->tail = nodePtr;
    }
    else
    {
        qPtr->tail->next = nodePtr;
        qPtr->tail = nodePtr;
    }
}
// PCB* dequeue(queue* qPtr)
// {
//     PCB* tempPCB = NULL;
//     if(qPtr == NULL)
//     {
//         err_msg("!ERROR! :: Attempt to dequeue from an empty queue.");
//     }
//     else
//     {
//         tempPCB = &(qPtr->head->data);
//         qPtr->head = qPtr->head->next;
//         if(qPtr->head == NULL)
//             qPtr->tail = NULL;
//     }
//    return tempPCB; 
// }
PCB* dequeue(queue* qPtr)
{
    queueNode* tempNode = NULL;
    if(qPtr == NULL)
    {
        err_msg("!ERROR! :: Attempt to dequeue from an empty queue.");
    }
    else
    {
        tempNode = qPtr->head;
        qPtr->head = qPtr->head->next;
        if(qPtr->head == NULL)
            qPtr->tail = NULL;
    }
    PCB* tempPCB = &(tempNode->data);
    kfree(tempNode);
    return tempPCB; 
}

void currProDeq(queue* qPtr)
{
    currProcess = dequeue(qPtr);
}
void currProEnq(queue* qPtr)
{
    enqueue(qPtr, makeNode(currProcess));
}
