#pragma once
//! A header alapötlete, hogy itt lesznek a classok definiálva, 
//! amik tulajdonságokkal látják el a tábla tartalmát
//! a lépések dekódolásakor
#include <iostream>
#include "board.h"
//! Célom öröklés megvalósítása virtuális destruktorral, 
//! és virtuális lépés validitás tesztelő függvénnyel
class piece {
	static board _board;
	//todo x,y helyett vector class
	int x, y;
	piece();
	virtual ~piece();
};