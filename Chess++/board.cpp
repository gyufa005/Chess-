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
        nextturn = true;
        //üresek
        for (int i = 0; i < 8; i++)
            for (int s = 2; s < 6; s++)
                boardcontents[s][i] = zero;
        //gyalogok
        for (int i = 0; i < 8; i++)
        {
            boardcontents[1][i] = 'p';
            boardcontents[6][i] = 'p';
        }
        //chatGPT
        boardcontents[0][0] = 'R';
        boardcontents[0][1] = 'T';
        boardcontents[0][2] = 'B';
        boardcontents[0][3] = 'Q';
        boardcontents[0][4] = 'T';
        boardcontents[0][5] = 'B';
        boardcontents[0][6] = 'T';
        boardcontents[0][7] = 'R';
        boardcontents[1][2] = 'M';
        boardcontents[1][5] = 'M';

        boardcontents[7][0] = 'r';
        boardcontents[7][1] = 't';
        boardcontents[7][2] = 'b';
        boardcontents[7][3] = 'q';
        boardcontents[7][4] = 't';
        boardcontents[7][5] = 'b';
        boardcontents[7][6] = 't';
        boardcontents[7][7] = 'r';
        boardcontents[6][2] = 'm';
        boardcontents[6][5] = 'm';
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
    static board b;
    if (b.nextturn)
    {
        for (int c = 0; c < 8; c++)
        {
            int colour = c % 2;
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
            for (int r = 0; r < 8; r++)
            {
                if ((colour + r) % 2)
                    printf("%c%c%c", whitesquare, b.boardcontents[c][r], whitesquare);
                else
                    printf("%c%c%c", blacksquare, b.boardcontents[c][r], blacksquare);

            }
            //alsó sor
            printf("\n");
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
        }
    }
    else
    {
        for (int c = 7; c >= 0; c--)
        {
            int colour = c % 2;
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
            for (int r = 7; r >= 0; r--)
            {
                if ((colour + r) % 2)
                    printf("%c%c%c", whitesquare, b.boardcontents[c][r], whitesquare);
                else
                    printf("%c%c%c", blacksquare, b.boardcontents[c][r], blacksquare);

            }
            //alsó sor
            printf("\n");
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
            // this->++nextturn%=2;
        }
    }
    b.nextturn = !b.nextturn;
    return;
    }

