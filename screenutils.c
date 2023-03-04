#include "screenutils.h"
#include "convert.h"

void initScreen()
{
    k_clearscr();
    print_border(0,0,MAXROW,MAXCOL);
    print_border(0,0,2,MAXCOL);
    k_printstr("[SYSTEM MESSAGE]",0,1);
    print_border(2,0,3,MAXCOL);
    k_printstr("[USER SPACE]",3,1);
    //corner_garf();
}

void splash_screen()
{
    k_printstr("       .-.,     ,.-.",4,1);
    k_printstr(" '-.  /:::\\\\   //:::\\  .-'",5,1);
    k_printstr(" '-.\\|':':' `\"` ':':'|/.-\'",6,1);
    k_printstr(" `-./`. .-=-. .-=-. .`\\.-`",7,1);
    k_printstr("   /=- /     |     \\ -=\\",8,1);
    k_printstr("  ;   |      |      |   ;",9,1);
    k_printstr("  |=-.|______|______|.-=|",10,1);
    k_printstr("  |==  \\  0 /_\\ 0  /  ==|",11,1);
    k_printstr("  |=   /'---( )---'\\   =|",12,1);
    k_printstr("   \\   \\:   .'.   :/   /",13,1);
    k_printstr("    `\\= '--`   `--' =/'",14,1);
    k_printstr("GARF  `-=._     _.=-'",15,1);
    k_printstr("OS v3.5a   `\"\"\"`",16,1);
}

void corner_garf()
{
    k_printstr("  |\\|\\",13,64);
    k_printstr(">/ ( )=<",14,64);
    k_printstr("|`'o' ==",15,64);
    k_printstr(" \\(^) =/",16,64);
    k_printstr("  `< =\"",17,64);
    k_printstr("  /  ||\"",18,64);
    k_printstr(" (   /)=\"",19,64);
    k_printstr("  \\ (,3=\"",20,64);
    k_printstr("   `++||==",21,64);
    k_printstr("  __||||`==.",22,64);
    k_printstr(" (,(,___\\ \"==)",23,64);
}

void print_border(int start_row, int start_col, int end_row, int end_col)
{
    //Draw line across start_row
    for(int i = start_col; i < end_col; i++)
        k_printstr("-", start_row, i);
    //Draw line across end_row
    for(int i = start_col; i < end_col; i++)
        k_printstr("-", end_row, i);
    //Draw line down start_col
    for(int i = start_row; i < end_row; i++)
        k_printstr("|", i, start_col);
    //Draw line down end_col
    for(int i = start_row; i < end_row; i++)
        k_printstr("|", i, end_col);
    //overwrite the corners with plus
    k_printstr("+", start_row, start_col);
    k_printstr("+", start_row, end_col);
    k_printstr("+", end_row, start_col);
    k_printstr("+", end_row, end_col);
}
void err_clear()
{
    for (int i = 1; i < 78; i++)
    {
        k_printstr(" ",1,i);
    }
}
void err_msg(char* msg)
{   //uses the last row of the screen before the border as a space to render error messages and exceptions.
    err_clear();
    k_printstr(msg, 1, 1);
}
