#pragma once
//! A header alap�tlete, hogy itt lesznek a classok defini�lva, 
//! amik tulajdons�gokkal l�tj�k el a t�bla tartalm�t
//! a l�p�sek dek�dol�sakor
#include <iostream>
#include "board.h"
//! C�lom �r�kl�s megval�s�t�sa virtu�lis destruktorral, 
//! �s virtu�lis l�p�s validit�s tesztel? f�ggv�nnyel
//! 
class piece {
	static board _board;
	piece();
	virtual ~piece();
};