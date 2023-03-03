#ifndef SCREENUTILS_H
#define SCREENUTILS_H

#include "io.h"

#define MAXROW 24
#define MAXCOL 79
#define NULL ((void*)0)

void initScreen();
void splash_screen();
void corner_garf();
void print_border(int start_row, int start_col, int end_row, int end_col);
void err_clear();
void err_msg(char* msg);

#endif //SCREENUTILS_H