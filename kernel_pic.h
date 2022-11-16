#ifndef KERNEL_PIC_H
#define KERNEL_PIC_H
#include <stdint.h>

extern void init_timer_dev(uint32_t timeDiv);
void outportb(uint16_t port, uint8_t data);
void setupPIC();

#endif