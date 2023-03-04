#include "usr_game.h"



void ent_print(char *s, int newrow, int newcol, int oldrow, int oldcol)
{
    k_printstr("#", newrow, newcol);
    k_printstr(" ", newrow, oldcol);
    k_printstr(" ", oldrow, newcol);
}

// void gameupdate(int &oldchrX, int &oldchrY, int &newchrX, int &newchrY)
// {
// }

void printLoc(int oldchrX, int oldchrY, int newchrX, int newchrY)
{
    char buff[3];
    k_printstr("X: ",22, 1);
    convert_num(newchrX, buff);
    k_printstr(buff, 22, 3);
    
    k_printstr("Y: ",22, 6);
    convert_num(newchrY, buff);
    k_printstr(buff, 22, 8);
    
    k_printstr("x: ",22, 11);
    convert_num(oldchrX, buff);
    k_printstr(buff, 22,13);
    
    k_printstr("y: ",22, 16);
    convert_num(oldchrY, buff);
    k_printstr(buff, 22, 18);

}

void proc_gameloop()
{
    char chrSymbol = '#';
    int chrX = GMAXCOL/2, 
        chrY = GMAXROW/2, 
        ochrX = GMAXCOL-1,
        ochrY = GMAXROW-1;
    int gameRun = 1;
    char keyPress = '0';
    int mvmt=1; //movement modifier


    err_msg("GAMETEST - us wasd to move the lil fella (#)");
    ent_print(&chrSymbol, chrY, chrX, ochrY, ochrX);
    printLoc(ochrX, ochrY, chrX, chrY);

    while(gameRun)
    {
        keyPress = k_getchar();
        switch(keyPress)
        {
            case 'w':
                if((chrY-mvmt) >= GMINROW)
                {
                    ochrY = chrY;
                    chrY = chrY-mvmt;

                    err_msg("MOVE: UP");
                    ent_print(&chrSymbol, chrY, chrX, ochrY, ochrX);
                    printLoc(ochrX, ochrY, chrX, chrY);
                }
                else
                {
                    err_msg("Can't go there!");
                }
                break;
            case 's':
                if((chrY+mvmt) <= GMAXROW)
                {
                    ochrY = chrY;
                    chrY = chrY+mvmt;

                    err_msg("MOVE: DOWN");
                    ent_print(&chrSymbol, chrY, chrX, ochrY, ochrX);
                    printLoc(ochrX, ochrY, chrX, chrY);
                }
                else
                {
                    err_msg("Can't go there!");
                }
                break;
            case 'a':
                if((chrX-mvmt) >= GMINCOL)
                {
                    ochrX = chrX;
                    chrX = chrX-mvmt;

                    err_msg("MOVE: LEFT");
                    ent_print(&chrSymbol, chrY, chrX, ochrY, ochrX);
                    printLoc(ochrX, ochrY, chrX, chrY);
                }
                else
                {
                    err_msg("Can't go there!");
                }
                break;
            case 'd':
                if((chrX+mvmt) <= GMAXCOL)
                {
                    ochrX = chrX;
                    chrX = chrX+mvmt;

                    err_msg("MOVE: RIGHT");
                    ent_print(&chrSymbol, chrY, chrX, ochrY, ochrX);
                    printLoc(ochrX, ochrY, chrX, chrY);
                }
                else
                {
                    err_msg("Can't go there!");
                }
                break;
            default:
                break;
        }
        
    }

}
