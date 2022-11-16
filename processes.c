#include "processes.h"
#include "screenutils.h"

void p1()
{
    print_border(10, 10, 13, 35);
    k_printstr("Process 1 running...", 11, 11);
    int num = 0;
    char buff[8];
    k_printstr("VALUE: ", 12, 11);
    while(1)
    {
        convert_num(num, buff);
        k_printstr(buff, 12, 18);
        num++;
        if (num > 999)
            num = 0;
    }
}

void p2()
{
    print_border(15,10,18,35);
    k_printstr("Process 2 running...", 16, 11);
    int num = 0;
    char buff[8];
    k_printstr("VALUE: ", 17, 11);
    while(1)
    {
        convert_num(num, buff);
        k_printstr(buff, 17, 18);
        num++;
        if (num > 999)
            num = 0;
    }
}