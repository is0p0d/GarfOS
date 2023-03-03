#include "kernel_kbd.h"

void kbd_handler(uint16 scancode)
{
    if (scancode < 0x2 || scancode > 0x80)
        return;
    else if(scancode == 0 || ring_buff_isfull(&kbd_buffer) == 1)
        return;
    ring_buff_push(&kbd_buffer, translate_scancode(scancode));
}
char translate_scancode(int code)
{
    if(code >= 0x2 && code <= 0xA)
        return cset_num_chars[code - 0x2];
    else if(code >= 0x10 && code <= 0x19)
        return cset_1_chars[code - 0x10];
    else if(code >= 0x1E && code <= 0x26)
        return cset_2_chars[code - 0x1E];
    else if(code >= 0x2C && code <= 0x32)
        return cset_3_chars[code - 0x2C];
    else
    {
        switch(code)
        {
            case 0x0B: 
                return '0';
                break;
            case 0x1C: 
                return '\n';
                break;
            case 0x39: 
                return ' ';
                break;
            case 0xE:  
                return '\n';
                break;
            case 0x34: 
                return '.';
                break;
            case 0x35: 
                return '/';
                break;
            default: 
                break;
        }
    }
}
char k_getchar()
{
    char temp;
    if(ring_buff_isfull(&kbd_buffer) == 2)
        return 0;
    else
    {
        ring_buff_pop(&kbd_buffer, &temp);
        return temp;
    }
}