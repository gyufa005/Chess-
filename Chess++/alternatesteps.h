#pragma once
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
//!!Az x és y irány fel lett cserélve a táblánál!! 
//! Ezt teljességében ebben a headerben oldom meg, 
//! de ez nem logikus elnevezésekhez vezet.
class coord {
	int x;
	int y;
public:
	coord(int x = 0, int y = 0) :x(x), y(y) {}
	int gety()const { return y; }
	int getx()const { return x; }
	const coord& getcoord()const { return *this; }
	void setcoord(int x, int y) { this->x = x; this->y = y; }
	friend std::istream& operator>>(std::istream& is, coord& coo);
	void convert() { this->x -= ('A'); }//EZ az asciit int értékére váltja
	//void operator=(const coord& r) { this->setcoord(r.getx(), r.gety()); }
};

std::istream& operator>>(std::istream& is, coord& coo) {
	char first;
	int second;
	is >> first >> second;
	first = std::toupper(first);
	if (first >= 'A' && first <= 'H' && second >= 1 && second <= 8) {
		coo.x = first - 'A';
		coo.y = second - 1;
		return is;
	}
	else
		throw "error reading step";
	return is;
}

class step {
	coord start;
	coord end;
public:
	coord getstart()const { return start; }
	coord getend()const { return end; }

	//! Tesztelő függvények
	//lépés hossza a nagyobb különbség a koordinátákból
	int lenght()const {
		int xe = end.getx();
		int ye = end.gety();
		int xs = start.getx();
		int ys = start.gety();	
		if (abs(xe-xs)>=abs(ye-ys))
			return abs(xe-xs);
		else return abs(ye-ys);
	}
	bool isStraight()const { return (end.getx() - start.getx() || end.gety() - start.gety()); }
	bool isYdir()const { return !(end.getx() - start.getx()); }
	bool isXdir()const { return (end.gety() - start.gety()==0); }
	bool isdiag()const {
		return (abs(end.getx() - start.getx()) == abs(end.gety() - start.gety()));
	}
	bool isForward()const { return ((end.gety() - start.gety()) > 0); }
	bool isRight()const { return ((end.getx() - start.getx()) > 0); }


	friend std::istream& operator>>(std::istream& is, step& s);
};
std::istream& operator>>(std::istream& is, step& s)
{
	is >> s.start >> s.end;
	return is;
}
