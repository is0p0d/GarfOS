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
#include "kernel_kbd.h"
#include "processes.h"


queue PCBqueue;
queue* PCBqueue_ptr = &PCBqueue;
PCB* currProcess;
int currPID = 100;
int retval = 0;

int main()
{
    //boot procedure
    initScreen();
    splash_screen();
    err_msg("Initializing heap: ");
    buddy_init(); // set up dynamic memory allocation
    err_msg("Initializing IDT...");
    initIDT();
    err_msg("Initializing process queue...");
    initqueue(PCBqueue_ptr);
    err_msg("Initializing keyboard buffer...");
    ring_buff_init(&kbd_buffer, charBuffer, MAX_BUF);
    char ch = '0';
    initScreen();
    //k_hidecursor(); see kernel.asm
    err_msg("GarfOS v3.0a :: [Test Branch] - Jim M, 2023");
    corner_garf();
    init_timer_dev(5);
    setupPIC();

    k_printstr("Press any key to clear the screen",4,1);

    while(1)
    {
        ch = k_getchar();
        if (ch != 0)
        {
            k_clearscr();
        }
    }
    // retval = create_process((uint32_t)&p1);
    // //include error handling
    // retval = create_process((uint32_t)&p2);

    // go();



    while(1); 
}