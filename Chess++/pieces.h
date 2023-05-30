#pragma once
//! A header alapötlete, hogy itt lesznek a classok definiálva, 
//! amik tulajdonságokkal látják el a tábla tartalmát
//! a lépések dekódolásakor
#include <iostream>
#include "board.h"
//! Célom öröklés megvalósítása virtuális destruktorral, 
//! és virtuális lépés validitás tesztelő függvénnyel
class piece {
protected:
	//true = white, false = black
	bool colour;
	coord location;
	const char idw;
	const char idb;
	piece(coord& c, char id1 = zero, char id2 = zero) :idw(id1), idb(id2) { location = c.getcoord(); }
public:
	char getP()const { if (colour)return idw; else return idb; }
	void operator!() { !(this->colour); return; }
	virtual ~piece();
};
class rook :public piece {
public:
	rook(coord& c):piece(c,'r','R'){}
};
class queen : public piece {
public:
	queen(coord& c) : piece(c,'q','Q'){}
};

class bishop : public piece {
public:
	bishop(coord& c) : piece(c,'b','B'){}
};

class pawn : public piece {
public:
	pawn(coord& c) : piece(c,'p','P'){}
};
class tower : public piece {
public: 
	tower(coord& c) : piece(c, 't', 'T') {}
};
class morph : public piece {
	piece* type;
public: 
	morph(coord& c) : piece(c, 'm', 'M') { type = new pawn(c); }
	~morph() { delete type; }
};