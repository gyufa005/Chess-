#pragma once 
#include "alternatesteps.h"
#include "pieces.h"
#include <iostream>
#define whitesquare 0xDB
#define blacksquare 0xFF
#define zero 0x20
class altboard {
    //piece heterogén kollekciója+ki következik a lépésben
	piece* boardcontents[8][8];
	bool white;
public: 
    bool wincond_check() {
        if ((boardcontents[7][6]->isTower() || boardcontents[7][4]->isTower() || boardcontents[7][1]->isTower()) &&
            (boardcontents[0][6]->isTower() || boardcontents[0][4]->isTower() || boardcontents[0][1]->isTower()))return false;
        else return false;
    }
    bool whowon() {//true = white , false = black
        if ((boardcontents[7][6]->isTower() || boardcontents[7][4]->isTower() || boardcontents[7][1]->isTower()))
            return false;
        else if (boardcontents[0][6]->isTower() || boardcontents[0][4]->isTower() || boardcontents[0][1]->isTower())
            return true;
        else
            throw "nobody won but whowon was called.";
    }
    //ez elvégzi a lépést
    void doMove(const step& s) {
        int i = s.getstart().getx();
        int j = s.getstart().gety();
        int k = s.getend().getx();
        int l = s.getend().gety();
        delete boardcontents[k][l];
        boardcontents[i][j]->changecoord(s.getend());
        boardcontents[k][l] = boardcontents[i][j];
        boardcontents[i][j] = new piece(i, j);
        return;
    }
    //ez megnézi van-e a lépés útjában valami
    bool checkmove(const step& s)const {
        //? lenght diagonálisan max(x,y)-t returnöl,nem vektor normát.
        for (int i = 0; i < s.lenght() - 1; i++)
        {
            if (s.isXdir())
            {
                if (!(isEmpty(s.getstart().getx() + i, s.getstart().gety())))return false;
            }
            else if (s.isYdir())
            {
                if (!(isEmpty(s.getstart().getx(), s.getstart().gety() + i)))return false;
            }
            else if (s.isdiag())
            {
                if (!(isEmpty(s.getstart().getx() + i, s.getstart().gety() + i)))return false;
            }
            else {
                throw"there is another piece in the way";
                    return false;
            }
        }
        return true;
    }
    bool isEmpty(int x,int y)const { return (boardcontents[x][y]->getP() == zero); }
    bool turncolour()const { return !white; }
    piece* at(coord& c)const {
        return boardcontents[c.getx()][c.gety()];
    }
    altboard() {
		std::cout << "Constructor runs";
        white = true;
        //üresek
        for (int i = 0; i < 8; i++)
            for (int s = 2; s < 6; s++)
                boardcontents[s][i]=new piece(s,i);
        //gyalogok
        for (int i = 0; i < 8; i++) {
            boardcontents[6][i] = new pawn(6, i);
            boardcontents[1][i] = new pawn(1,i);
        }
        //tisztek
        boardcontents[7][0] = new rook(7,0);
        boardcontents[7][1] = new tower(7,1);
        boardcontents[7][2] = new bishop(7,2);
        boardcontents[7][3] = new queen(7,3);
        boardcontents[7][4] = new tower(7,4);
        boardcontents[7][5] = new bishop(7,5);
        boardcontents[7][6] = new tower(7,6);
        boardcontents[7][7] = new rook(7,7);
        delete boardcontents[6][2], boardcontents[6][5];
        boardcontents[6][2] = new morph(6,2);
        boardcontents[6][5] = new morph(6,5);

        boardcontents[0][0] = new rook(0,0);
        boardcontents[0][1] = new tower(0,1);
        boardcontents[0][2] = new bishop(0,2);
        boardcontents[0][3] = new queen(0,3);
        boardcontents[0][4] = new tower(0,4);
        boardcontents[0][5] = new bishop(0,5);
        boardcontents[0][6] = new tower(0,6);
        boardcontents[0][7] = new rook(0,7);
        //2 gyalog helyett morph
        delete boardcontents[1][2], boardcontents[1][5];
        boardcontents[1][2] = new morph(1,2);
        boardcontents[1][5] = new morph(1,5);
        //fekete bábuk színe
        for (int i = 0; i < 8; i++) {
            boardcontents[7][i]->colorchange();
            boardcontents[6][i]->colorchange();
        }

    }
    ~altboard() {
        std::cout << "destructor runs";
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                delete boardcontents[i][j];
            }
        }
        for (int i = 0; i < 8; i++)
            delete[] boardcontents[i];
        delete[] boardcontents;
    }
    void drawboard() {//c=column, r=row

        if (white)
        {

            printf("  a  b  c  d  e  f  g  h  \n");
            for (int c = 7; c >= 0; c--)
            {
                std::cout << " ";
                int colour = (c + 1) % 2;
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
                std::cout << c + 1;
                for (int r = 7; r >= 0; r--)
                {
                    if ((colour + r) % 2)
                        printf("%c%c%c", whitesquare, boardcontents[c][r]->getP(), whitesquare);
                    else
                        printf("%c%c%c", blacksquare, boardcontents[c][r]->getP(), blacksquare);

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
            printf("  a  b  c  d  e  f  g  h  \n");
        }
        else
        {
            printf("  h  g  f  e  d  c  b  a  \n");
            for (int c = 0; c < 8; c++)
            {
                std::cout << " ";
                int colour = (c + 1) % 2;
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
                std::cout << c + 1;
                for (int r = 0; r < 8; r++)
                {
                    if ((colour + r) % 2)
                        printf("%c%c%c", whitesquare, boardcontents[c][r]->getP(), whitesquare);
                    else
                        printf("%c%c%c", blacksquare, boardcontents[c][r]->getP(), blacksquare);

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
                // this->++white%=2;
                
            }
            printf("  h  g  f  e  d  c  b  a  \n");
        }
        white = !white;
        return;

    }
	
};