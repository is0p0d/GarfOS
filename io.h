#ifndef IO_H
#define IO_H

void k_hidecursor();
void k_print(char *s, int len, int row, int col);
void k_printstr(char *s, int row, int col);
void k_clearscr();

#endif //IO_H