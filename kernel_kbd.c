#include "kernel_kbd.h"

ring_buffer kbd_buffer;
char charBuffer[MAX_BUF];


//buffer functions
//===========================================================================
void ring_buff_init(ring_buffer* passedStruct, char* passedBuff, uint8_t buffLength)
{
    passedStruct->buffer = passedBuff;
    passedStruct->first = 0;
    passedStruct->last = 0;
    passedStruct->buffMax = buffLength;
}
void ring_buff_push(ring_buffer* buff, char data)
{
    uint8_t writeNext;
    writeNext = buff->first + 1; //where to point after writing
    //position logic
    if (writeNext >= buff->buffMax)
        writeNext = 0;
    if (writeNext == buff->last) //if buffer is full, overwrite the next position
        buff->last++;
    buff->buffer[buff->first] = data; //Write data to beginning of buffer
    buff->first = writeNext;
}
void ring_buff_pop(ring_buffer* buff, char* data)
{
    uint8_t readNext;

    if (buff->first == buff->last) //buffer is empty if this is true
    {
        return;
        println("!!ERROR: ring buffer EMPTY");
    }

    readNext = buff->last + 1; //where to point after reading
    if(readNext >= buff->buffMax)
        readNext = 0;
    
    *data = buff->buffer[buff->last]; //read data
    buff->last = readNext; //move to next offset
}
uint8_t ring_buff_isfull(ring_buffer* buff)
{
    if((buff->first)+1 == buff->last) // buff is full
        return 1;
    else if (buff->first == buff->last) // buff is empty
        return 2;
    else // buff has stuff in it
        return 0;
}

//keyboard functions
//===========================================================================

void kbd_handler(uint16_t scancode)
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