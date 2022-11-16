#include "kernel_idt.h"

idt_entry idt[256];
idt_ptr limitStruct;

void default_exception()
{
    err_msg("!EXCEPTION! :: Default Exception");
    while(1);
}
void interrupt_0()
{
    err_msg("!EXCEPTION! :: 0x0 Divide by Zero");
    while(1);
}
void interrupt_1()
{
    err_msg("!EXCEPTION! :: 0x01 Debug error");
    while(1);
}
void interrupt_2()
{
    err_msg("!EXCEPTION! :: 0x02 Non-Maskable Interrupt");
    while(1);
}
void interrupt_3()
{
    err_msg("!EXCEPTION! :: 0x03 Breakpoint error");
    while(1);
}
void interrupt_4()
{
    err_msg("!EXCEPTION! :: 0x04 Overflow error");
    while(1);
}
void interrupt_5()
{
    err_msg("!EXCEPTION! :: 0x05 Bound Rage Exceeded");
    while(1);
}
void interrupt_6()
{
    err_msg("!EXCEPTION! :: 0x06 Invalid Opcode");
    while(1);
}
void interrupt_7()
{
    err_msg("!EXCEPTION! :: 0x07 Coprocessor Unavailable");
    while(1);
}
void interrupt_8()
{
    err_msg("!EXCEPTION! :: 0x08 Double Fault");
    while(1);
}
void interrupt_9()
{
    err_msg("!EXCEPTION! :: 0x09 Coprocessor Segment Overrun");
    while(1);
}
void interrupt_10()
{
    err_msg("!EXCEPTION! :: 0x0A Invalid Task State Segment");
    while(1);
}
void interrupt_11()
{
    err_msg("!EXCEPTION! :: 0x0B Segment Not Present");
    while(1);
}
void interrupt_12()
{
    err_msg("!EXCEPTION! :: 0x0C Stack Exception");
    while(1);
}
void interrupt_13()
{
    err_msg("!EXCEPTION! :: 0x0D General Protection Exception");
    while(1);
}
void interrupt_14()
{
    err_msg("!EXCEPTION! :: 0x0E Page Fault");
    while(1);
}
void interrupt_15()
{
    err_msg("!EXCEPTION! :: 0x0F Reserved (how did you get here?)");
    while(1);
}
void interrupt_16()
{
    err_msg("!EXCEPTION! :: 0x10 Coprocessor Error");
    while(1);
}
void initIDTEntry(idt_entry *entry, uint32_t base, uint16_t selector, uint8_t access)
{
    entry->base_low16 = (uint16_t)(base & 0xFFFF);
    entry->base_high16 = (uint16_t)((base >> 16) & 0xFFFF);
    entry->always0 = 0;
    entry->access = access;
    entry->selector = selector;
}
void initIDT()
{
    for (int i = 0; i < 256; i++)
    {
        switch(i)
        {
            case 0: initIDTEntry(&idt[i], (uint32_t)&interrupt_0, 0x10, 0x8e);
                    break;
            case 1: initIDTEntry(&idt[i], (uint32_t)&interrupt_1, 0x10, 0x8e);
                    break;
            case 2: initIDTEntry(&idt[i], (uint32_t)&interrupt_2, 0x10, 0x8e);
                    break;
            case 3: initIDTEntry(&idt[i], (uint32_t)&interrupt_3, 0x10, 0x8e);
                    break;
            case 4: initIDTEntry(&idt[i], (uint32_t)&interrupt_4, 0x10, 0x8e);
                    break;
            case 5: initIDTEntry(&idt[i], (uint32_t)&interrupt_5, 0x10, 0x8e);
                    break;
            case 6: initIDTEntry(&idt[i], (uint32_t)&interrupt_6, 0x10, 0x8e);
                    break;
            case 7: initIDTEntry(&idt[i], (uint32_t)&interrupt_7, 0x10, 0x8e);
                    break;
            case 8: initIDTEntry(&idt[i], (uint32_t)&interrupt_8, 0x10, 0x8e);
                    break;
            case 9: initIDTEntry(&idt[i], (uint32_t)&interrupt_9, 0x10, 0x8e);
                    break;
            case 10: initIDTEntry(&idt[i], (uint32_t)&interrupt_10, 0x10, 0x8e);
                    break;
            case 11: initIDTEntry(&idt[i], (uint32_t)&interrupt_11, 0x10, 0x8e);
                    break;
            case 12: initIDTEntry(&idt[i], (uint32_t)&interrupt_12, 0x10, 0x8e);
                    break;
            case 13: initIDTEntry(&idt[i], (uint32_t)&interrupt_13, 0x10, 0x8e);
                    break;
            case 14: initIDTEntry(&idt[i], (uint32_t)&interrupt_14, 0x10, 0x8e);
                    break;
            case 15: initIDTEntry(&idt[i], (uint32_t)&interrupt_15, 0x10, 0x8e);
                    break;
            case 16: initIDTEntry(&idt[i], (uint32_t)&interrupt_16, 0x10, 0x8e);
                    break;
            default:
                if (i > 16 && i < 32 )
                    initIDTEntry(&idt[i], (uint32_t)&default_exception, 0x10, 0x8e);
                else if (i == 32)
                    initIDTEntry(&idt[i], (uint32_t)&dispatch, 0x10, 0x8e);
                else    
                    initIDTEntry(&idt[i], 0, 0x10, 0x8e);
                break;
        }
    }

    limitStruct.limit = (sizeof(idt_entry) * 256) - 1;
    limitStruct.base = (uint32_t)&idt;

    asm volatile ("lidt (%0)" : : "r" (&limitStruct));

    return;

    //lidtr(&limitStruct);
}