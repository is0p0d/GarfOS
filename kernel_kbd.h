#ifndef KERNEL_KBD_H
#define KERNEL_KBD_H

#include <stdint.h>
#include "kbd_characters.h"

#define MAX_BUF 64

struct ring_buffer_struct
{
    char* buffer;
    uint8_t first;
    uint8_t last;
    uint8_t buffMax;

}__attribute__((packed));
typedef struct ring_buffer_struct ring_buffer;

void ring_buff_init(ring_buffer* passedStruct, char* passedBuff, uint8_t buffLength);
void ring_buff_push(ring_buffer* buff, char data);
void ring_buff_pop(ring_buffer* buff, char* data);
uint8_t ring_buff_isfull(ring_buffer* buff);

//keyboard function prototypes
//===========================================================================
void kbd_enter();                                               //asm boot2.s
void kbd_handler(uint16_t scancode);
char translate_scancode(int code);
char k_getchar();

extern ring_buffer kbd_buffer;
extern char charBuffer[MAX_BUF];

#endif //KERNEL_KBD_H