/********************************************************
 * Jim Moroney                                 09.16.22 *
 * kernel.c                        CSC4100 - Homework 1 *
 * Required Files:                                      *
 * kernel.c, kernel.asm, boot1.asm, buddy.h, convert.h, *
 * io.h, screenutils.h                                  *
 *******************************************************/
#include "io.h"
#include "buddy.h"
#include "convert.h"
#include "screenutils.h"
#include "kernel_pcb.h"
#include "kernel_idt.h"
#include "kernel_pic.h"
#include "processes.h"


queue PCBqueue;
queue* PCBqueue_ptr = &PCBqueue;
PCB* currProcess;
int currPID = 100;
int retval = 0;

int main()
{
    buddy_init(); // set up dynamic memory allocation
    initIDT();
    initqueue(PCBqueue_ptr);
    initScreen();
    //k_hidecursor(); see kernel.asm

    init_timer_dev(5);
    setupPIC();

    retval = create_process((uint32_t)&p1);
    //include error handling
    retval = create_process((uint32_t)&p2);

    go();

    while(1); 
}