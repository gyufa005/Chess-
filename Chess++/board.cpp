#include "board.h"
#include <iostream>
#include <stdio.h>
//char** board::boardcontents = nullptr;
char board::boardcontents[8][8];
board::board() {
    {
        std::cout << "constructor runs\n";
        //dinamikus foglalás a táblának
        /*boardcontents = new char* [size];
        for (int i = 0; i < size; i++)
            boardcontents[i] = new char[size];
        */
        blknext = true;
        //üresek
        for (int i = 0; i < 8; i++)
            for (int s = 2; s < 6; s++)
                boardcontents[s][i] = zero;
        //gyalogok
        for (int i = 0; i < 8; i++) {
            boardcontents[1][i] = 'P';
            boardcontents[6][i] = 'p';
        }
        //ChatGPT
        boardcontents[7][0] = 'R';
        boardcontents[7][1] = 'T';
        boardcontents[7][2] = 'B';
        boardcontents[7][3] = 'Q';
        boardcontents[7][4] = 'T';
        boardcontents[7][5] = 'B';
        boardcontents[7][6] = 'T';
        boardcontents[7][7] = 'R';
        boardcontents[6][2] = 'M';
        boardcontents[6][5] = 'M';

        boardcontents[0][0] = 'r';
        boardcontents[0][1] = 't';
        boardcontents[0][2] = 'b';
        boardcontents[0][3] = 'q';
        boardcontents[0][4] = 't';
        boardcontents[0][5] = 'b';
        boardcontents[0][6] = 't';
        boardcontents[0][7] = 'r';
        boardcontents[1][2] = 'm';
        boardcontents[1][5] = 'm';

    }
}
board::~board() {
    /*for (int i = 0; i < size; i++)
        delete[] boardcontents[i];
    delete[] boardcontents;*/
    std::cerr<< "destructor runs\n"<<std::endl;
}
void board::drawboard()
{//c=column, r=row
   
    if (blknext)
    {
        
        printf("  a  b  c  d  e  f  g  h  \n");
        for (int c = 7; c >= 0; c--)
        {
            std::cout << " ";
            int colour = (c+1) % 2;
            for (int i = 0; i < 4; i++)
            {
                //felső keret
                if (!colour)
                {
                    printf("%c%c%c", whitesquare, whitesquare, whitesquare);
                    printf("%c%c%c", blacksquare, blacksquare, blacksquare);
                }
                else {
                    printf("%c%c%c", blacksquare, blacksquare, blacksquare);
                    printf("%c%c%c", whitesquare, whitesquare, whitesquare);
                }
            }
            printf("\n");
            //középső sor
            std::cout << c+1;
            for (int r = 7; r >= 0; r--)
            {
                if ((colour + r) % 2)
                    printf("%c%c%c", whitesquare, boardcontents[c][r], whitesquare);
                else
                    printf("%c%c%c", blacksquare, boardcontents[c][r], blacksquare);

            }
            //alsó sor
            printf("\n");
            std::cout << " ";
            for (int i = 0; i < 4; i++)
            {
                if (!colour)
                {
                    printf("%c%c%c", whitesquare, whitesquare, whitesquare);
                    printf("%c%c%c", blacksquare, blacksquare, blacksquare);
                }
                else {
                    printf("%c%c%c", blacksquare, blacksquare, blacksquare);
                    printf("%c%c%c", whitesquare, whitesquare, whitesquare);
                }
            }
            printf("\n");
        }
    }
    else
    {
        printf("  h  g  f  e  d  c  b  a  \n");
        for (int c = 0; c < 8; c++)
        {
            std::cout <<" ";
            int colour = (c+1) % 2;
            for (int i = 0; i < 4; i++)
            {
                //felső keret
                if (colour)
                {
                    printf("%c%c%c", whitesquare, whitesquare, whitesquare);
                    printf("%c%c%c", blacksquare, blacksquare, blacksquare);
                }
                else {
                    printf("%c%c%c", blacksquare, blacksquare, blacksquare);
                    printf("%c%c%c", whitesquare, whitesquare, whitesquare);
                }
            }
            printf("\n");
            //középső sor
            std::cout <<c+1;
            for (int r = 0; r < 8; r++)
            {
                if ((colour + r) % 2)
                    printf("%c%c%c", whitesquare, boardcontents[c][r], whitesquare);
                else
                    printf("%c%c%c", blacksquare, boardcontents[c][r], blacksquare);

            }
            //alsó sor
            printf("\n");
            std::cout << " ";
            for (int i = 0; i < 4; i++)
            {
                if (colour)
                {
                    printf("%c%c%c", whitesquare, whitesquare, whitesquare);
                    printf("%c%c%c", blacksquare, blacksquare, blacksquare);
                }
                else {
                    printf("%c%c%c", blacksquare, blacksquare, blacksquare);
                    printf("%c%c%c", whitesquare, whitesquare, whitesquare);
                }
            }
            printf("\n");
            // this->++blknext%=2;
        }
    }
    blknext = !blknext;
    return;
    }

