#pragma once
//! A header alapötlete, hogy itt lesznek a classok definiálva, 
//! amik tulajdonságokkal látják el a tábla tartalmát
//! a lépések dekódolásakor
#include <iostream>
//#include "altboard.h"
//! Célom öröklés megvalósítása virtuális destruktorral, 
//! és virtuális lépés validitás tesztelő függvénnyel
class piece {//! Ez alapból az "üres" bábu 
protected:
	//true = white, false = black
	bool colour;
	coord location;
	const char idw;
	const char idb;
	
public:
	piece(int x,int y, char id1 = zero, char id2 = zero) :idw(id1), idb(id2) { location.setcoord(x,y); colour = true; }
	char getP()const { if (colour)return idw; else return idb; }
	bool getC()const { return colour; }
	void colorchange() { this->colour=!this->colour; return; }
	virtual ~piece() {}
	virtual bool canitmove(const step& s)const {
		return false;
	}
	void changecoord(const coord& c)
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
	rook(int x,int y):piece(x,y,'r','R'){}
};
class queen : public piece {
public:
	
	bool canitmove(const step& s)const override { if (s.isStraight() || s.isdiag())return true; else return false; }
	queen(int x,int y) : piece(x,y,'q','Q'){}
};

class bishop : public piece {
public:
	
	bool canitmove(const step& s)const override { if (s.isdiag())return true; }
	bishop(int x,int y) : piece(x,y,'b','B'){}
};

class pawn : public piece {
public:
	bool canitmove(const step& s)const override {
		if (s.lenght() == 1 && ((this->colour == true && s.isForward()) || (this->colour == false && !s.isForward())))
			return true; else return false;
	}
	pawn(int x,int y) : piece(x,y,'p','P'){}
};
class tower : public piece {
public: 
	bool isTower()override { return true; }
	bool canitmove(const step& s)const override { return false; }
	tower(int x,int y) : piece(x,y, 't', 'T') {}
};
class morph : public piece {
	piece* type;
public: 
	bool canitmove(const step& s)const override { return type->canitmove(s); }
	morph(int x,int y) : piece(x,y, 'm', 'M') { type = new pawn(x,y); }
	~morph() { delete type; }
};