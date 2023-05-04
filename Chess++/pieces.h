#pragma once
//! A header alapötlete, hogy itt lesznek a classok definiálva, 
//! amik tulajdonságokkal látják el a tábla tartalmát
//! a lépések dekódolásakor
#include <iostream>
#include "board.h"
//! Célom öröklés megvalósítása virtuális destruktorral, 
//! és virtuális lépés validitás tesztel? függvénnyel
//! 
class piece {
	static board _board;
	piece();
	virtual ~piece();
};