#pragma once

//! A header alapötlete, hogy itt lesznek a classok definiálva, 
//! amik tulajdonságokkal látják el a tábla tartalmát
//! a lépések dekódolásakor
#include <iostream>
//#include "altboard.h"
//! Célom öröklés megvalósítása virtuális destruktorral, 
//! és virtuális lépés validitás tesztelő függvénnyel
#define whitesquare 0xDB
#define blacksquare 0xFF
#define zero 0x20
class piece {//! Ez alapból az "üres" bábu 
protected:
	//1 = white, 0 = black, 2=blank
	int colour;
	coord location;
	const char idw;
	const char idb;

public:
	piece(int tx, int ty, char id1 = zero, char id2 = zero) :idw(id1), idb(id2) { colour = 2; location.setcoord(tx, ty); }
	char getP()const { if (colour==1)
		return idw; else return idb; }
	bool getC()const { return colour; }
	virtual void colorchange() { if (colour = 0)colour++; else if (colour = 1)colour--; return; }
	virtual ~piece() {}
	virtual bool canitmove(const step& s)const {
		return false;
	}
	virtual void changecoord(const coord& c)
	{
		location = c;
		return;
	}
	virtual bool isTower() { return false; }
};
class rook :public piece {
public:

	bool canitmove(const step& s)const override {
		if (s.isStraight())
			return true;
		else return false;
	}
	rook(int x, int y) :piece(x, y, 'r', 'R') { colour = 1; }
};
class queen : public piece {
public:

	bool canitmove(const step& s)const override { if (s.isStraight() || s.isdiag())return true; else return false; }
	queen(int x, int y) : piece(x, y, 'q', 'Q') { colour = 1; }
};

class bishop : public piece {
public:

	bool canitmove(const step& s)const override { if (s.isdiag())return true; }
	bishop(int x, int y) : piece(x, y, 'b', 'B') { colour = 1; }
};

class pawn : public piece {
	int hasstepped;
public:
	void changecoord(const coord& c)
	{
		hasstepped++;
		location = c;
		return;
	}
	bool canitmove(const step& s)const override {
		bool tr = (this->colour == 0 && s.isForward() == false);
		int sl = s.lenght();
		if (((this->hasstepped == 0 && s.lenght() == 2) || s.lenght() == 1) &&
			((this->colour == 1 && s.isForward()) || (this->colour == 0 && s.isForward()==false)))
		{
			return true;
		}
		else return false;
	}
	pawn(int x, int y) : piece(x, y, 'p', 'P') { hasstepped = 0; colour = 1; }
};
class tower : public piece {
public:
	bool isTower()override { return true; }
	bool canitmove(const step& s)const override { return false; }
	tower(int x, int y) : piece(x, y, 't', 'T') { colour = 1; }
};
class morph : public piece {
	piece* type;
public:
	bool canitmove(const step& s)const override { return type->canitmove(s); }
	morph(int x, int y) : piece(x, y, 'm', 'M') { type = new pawn(x, y); colour = 1; }
	~morph() { delete type; }
	void colorchange()override {
		if (colour = 0) {
			colour++;
			type->colorchange();
		}
		else if (colour = 1) {
			colour--;
			type->colorchange();
		} return;
	}
	void changecoord(const coord& c) override
	{
		location = c;
		type->changecoord(c);
		return;
	}
	
};
