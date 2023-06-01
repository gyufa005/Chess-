#pragma once
#include "alternatesteps.h"
#include "pieces.h"
#include <iostream>

class altboard {
    //piece heterogén kollekciója+ki következik a lépésben
    piece* boardcontents[8][8];
    bool white;
public:
    bool wincond_check() {
        if ((boardcontents[6][7]->isTower() || boardcontents[4][7]->isTower() || boardcontents[1][7]->isTower()) &&
            (boardcontents[6][0]->isTower() || boardcontents[4][0]->isTower() || boardcontents[1][0]->isTower()))return false;
        else return true;
    }
    bool whowon() {//true = white , false = black
        if ((boardcontents[6][7]->isTower() || boardcontents[4][7]->isTower() || boardcontents[1][7]->isTower()))
            return false;
        else if (boardcontents[6][0]->isTower() || boardcontents[4][0]->isTower() || boardcontents[1][0]->isTower())
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
        this->boardcontents[i][j]->changecoord(s.getend());
        delete this->boardcontents[k][l];
        this->boardcontents[k][l] = this->boardcontents[i][j];
        this->boardcontents[i][j] = new piece(i, j);
        return;
    }
    //ez megnézi van-e a lépés útjában valami
    bool checkmove(const step& s)const {
        //? lenght diagonálisan max(x,y)-t returnöl,nem vektor normát.
        int x = s.getstart().getx();
        int y = s.getstart().gety();
        for (int i = 1; i < s.lenght(); i++)
        {
            if (s.isXdir())
            {
                char c;
                if (s.isRight() == true)
                    c = this->boardcontents[x + i][y]->getP();
                else
                    c = this->boardcontents[x - i][y]->getP();
                if (c != zero) {
                    throw "there is another piece in the way";
                    return false;
                }
            }
            else if (s.isYdir())
            {
                char c;
                if(s.isForward()==true)
                    c = this->boardcontents[x][y+i]->getP();
                else 
                    c= this->boardcontents[x][y - i]->getP();
                if (c != zero) {
                    throw "there is another piece in the way";
                    return false;
                }
            }
            else if (s.isdiag())
            {
                char c;
                if (s.isForward() && s.isRight()) {
                    c = this->boardcontents[x + i][y + i]->getP();
                }
                if (s.isForward()==true && s.isRight() == false) {
                    {
                        c = this->boardcontents[x - i][y + i]->getP();
                    }
                }
                if (s.isForward() == false && s.isRight()==true)
                {
                    {
                        c = this->boardcontents[x + i][y - i]->getP(); 
                    }
                }
                if(s.isForward()==false&&s.isRight()==false)
                             c = this->boardcontents[x - i][y - i]->getP();
                if (c != zero)
                {
                    throw "there is another piece in the way";
                    return false;
                }
            }
            else {
                throw"there is another piece in the way";
                return false;
            }
        }
        return true;
    }
    bool isEmpty(int x, int y)const { return (boardcontents[x][y]->getP() == zero); }
    bool turncolour()const { return !white; }
    piece* at(coord& c)const {
        return boardcontents[c.getx()][c.gety()];
    }
    altboard() {
        std::cout << "Constructor runs\n";
        white = true;
        //üresek
        for (int i = 0; i < 8; i++)
            for (int s = 2; s < 6; s++)
                boardcontents[i][s] = new piece(i, s);
        //gyalogok
        for (int i = 0; i < 8; i++) {
            boardcontents[i][1] = new pawn(i, 1);
            boardcontents[i][6] = new pawn(i, 6);
        }
        //tisztek
        boardcontents[0][7] = new rook(0,7);
        boardcontents[1][7] = new tower(1, 7);
        boardcontents[2][7] = new bishop(2, 7);
        boardcontents[3][7] = new queen(3, 7);
        boardcontents[4][7] = new tower(4, 7);
        boardcontents[5][7] = new bishop(5, 7);
        boardcontents[6][7] = new tower(6, 7);
        boardcontents[7][7] = new rook(7, 7);
        delete boardcontents[2][6], boardcontents[5][6];
        boardcontents[2][6] = new morph(2, 6);
        boardcontents[5][6] = new morph(5, 6);

        boardcontents[0][0] = new rook(0, 0);
        boardcontents[1][0] = new tower(1, 1);
        boardcontents[2][0] = new bishop(2, 0);
        boardcontents[3][0] = new queen(3, 0);
        boardcontents[4][0] = new tower(4, 0);
        boardcontents[5][0] = new bishop(5, 0);
        boardcontents[6][0] = new tower(6, 0);
        boardcontents[7][0] = new rook(7, 0);
        //2 gyalog helyett morph
        delete boardcontents[2][1], boardcontents[5][1];
        boardcontents[2][1] = new morph(2,1);
        boardcontents[5][1] = new morph(5,1);
        //fekete bábuk színe
        for (int i = 0; i < 8; i++) {
            boardcontents[i][7]->colorchange();
            boardcontents[i][6]->colorchange();
        }
    }
    ~altboard() {
        std::cout << "destructor runs\n";
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
                for (int r = 7; r >= 0;r--)////////////////////
                {
                    if ((colour + r) % 2)
                        printf("%c%c%c", whitesquare, boardcontents[7-r][c]->getP(), whitesquare);
                    else
                        printf("%c%c%c", blacksquare, boardcontents[7-r][c]->getP(), blacksquare);

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
            printf("  a  b  c  d  e  f  g  h  \n");
            for (int c=0;c<8;c++)
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
                std::cout << c+1;
                for (int r = 0; r < 8; r++)
                {
                    if ((colour + r) % 2)
                        printf("%c%c%c", whitesquare, boardcontents[r][c]->getP(), whitesquare);
                    else
                        printf("%c%c%c", blacksquare, boardcontents[r][c]->getP(), blacksquare);

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
            printf("  a  b  c  d  e  f  g  h  \n");
        }
        white = !white;
        return;

    }

};
/*
std::cout << "Constructor runs";
white = true;
//üresek
for (int i = 0; i < 8; i++)
    for (int s = 2; s < 6; s++)
        boardcontents[s][i] = new piece(s, i);
//gyalogok
for (int i = 0; i < 8; i++) {
    boardcontents[6][i] = new pawn(6, i);
    boardcontents[1][i] = new pawn(1, i);
}
//tisztek
boardcontents[7][0] = new rook(7, 0);
boardcontents[7][1] = new tower(7, 1);
boardcontents[7][2] = new bishop(7, 2);
boardcontents[7][3] = new queen(7, 3);
boardcontents[7][4] = new tower(7, 4);
boardcontents[7][5] = new bishop(7, 5);
boardcontents[7][6] = new tower(7, 6);
boardcontents[7][7] = new rook(7, 7);
delete boardcontents[6][2], boardcontents[6][5];
boardcontents[6][2] = new morph(6, 2);
boardcontents[6][5] = new morph(6, 5);

boardcontents[0][0] = new rook(0, 0);
boardcontents[0][1] = new tower(0, 1);
boardcontents[0][2] = new bishop(0, 2);
boardcontents[0][3] = new queen(0, 3);
boardcontents[0][4] = new tower(0, 4);
boardcontents[0][5] = new bishop(0, 5);
boardcontents[0][6] = new tower(0, 6);
boardcontents[0][7] = new rook(0, 7);
//2 gyalog helyett morph
delete boardcontents[1][2], boardcontents[1][5];
boardcontents[1][2] = new morph(1, 2);
boardcontents[1][5] = new morph(1, 5);
//fekete bábuk színe
for (int i = 0; i < 8; i++) {
    boardcontents[7][i]->colorchange();
    boardcontents[6][i]->colorchange();
}
*/
