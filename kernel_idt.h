#ifndef KERNEL_IDT_H
#define KERNEL_IDT_H
#include <stdint.h>

extern void dispatch();

extern void kbd_enter();

struct idt_entry_struct
{
    uint16_t base_low16;
    uint16_t selector;
    uint8_t  always0;
    uint8_t access;
    uint16_t base_high16;
} __attribute__((packed));  //compress for memory efficiency
                            //safety isn't a concern because this all
                            //fits in a relatively neat spot in ram
typedef struct idt_entry_struct idt_entry;

struct idt_ptr_struct
{
    uint16_t limit;
    uint32_t base;
}__attribute__((packed));
typedef struct idt_ptr_struct idt_ptr;

void default_exception();
void interrupt_0();
void interrupt_1();
void interrupt_2();
void interrupt_3();
void interrupt_4();
void interrupt_5();
void interrupt_6();
void interrupt_7();
void interrupt_8();
void interrupt_9();
void interrupt_10();
void interrupt_11();
void interrupt_12();
void interrupt_13();
void interrupt_14();
void interrupt_15();
void interrupt_16();
void initIDTEntry(idt_entry *entry, uint32_t base, uint16_t selector, uint8_t access);
void initIDT();

extern idt_entry idt[256];
extern idt_ptr limitStruct;

#endif