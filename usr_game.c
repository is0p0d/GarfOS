#include "usr_game.h"

//maps
//0 is space, 1 is wall, 2 is enemy, 3 is powerup
int testmap[20][78] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,1,1,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,1,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};



//code

void ent_print(char *s, int newrow, int newcol, int oldrow, int oldcol)
{
    k_printstr(" ", newrow, oldcol);
    k_printstr(" ", oldrow, newcol);
    k_printstr("&", newrow, newcol);
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

void renderMap(int mapName[GMAXROW][GMAXCOL])
{
    for(int rowIdx = 0; rowIdx < GMAXROW-3; rowIdx++)
    {
        for(int colIdx = 0; colIdx < GMAXCOL; colIdx++)
        {
            switch(mapName[rowIdx][colIdx])
            {
                case 0:
                    k_printstr(" ", rowIdx+4, colIdx+1);
                    break;
                case 1:
                    k_printstr("#", rowIdx+4, colIdx+1);
                    break;
                case 2:
                    k_printstr("!", rowIdx+4, colIdx+1);
                    break;
                case 3:
                    k_printstr("+", rowIdx+4, colIdx+1);
                    break;
                default:
                    err_msg("GAMETEST - MAP READ ERROR!");
                    break;
            }
        }
    }
}

void proc_gameloop()
{
    char chrSymbol = '&';
    int chrX = GMAXCOL/2, 
        chrY = GMAXROW/2, 
        ochrX = chrX,
        ochrY = chrY;
    int gameRun = 1;
    char keyPress = '0';
    int mvmt=1; //movement modifier

    err_msg("GAMETEST - Rendering map...");
    renderMap(testmap);
    err_msg("GAMETEST - us wasd to move the lil fella (&)");
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
