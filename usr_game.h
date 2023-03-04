#ifndef USR_GAME_H
#define USR_GAME_H

#include "io.h"
#include "screenutils.h"
#include "kernel_kbd.h"

#define GMAXCOL 78
#define GMAXROW 23
#define GMINCOL 1
#define GMINROW 4


//entity print
//prints an character to screen and erases the previous location of the character
void ent_print(char *s, int newrow, int newcol, int oldrow, int oldcol);
//void gameupdate(int oldchrX, int oldchrY, int newchrX, int newchrY);
void printLoc(int oldchrX, int oldchrY, int newchrX, int newchrY);
void proc_gameloop();


#endif