#pragma once
#include <stdio.h>
#include <iostream>
class coord {
	int x;
	int y;
public:
	coord() :x(0),y(0) {}
	int gety()const { return y; }
	int getx()const { return x; }
	const coord& getcoord()const { return *this; }
	void setcoord(int x = 0, int y = 0) { x = x; y = y; }
	friend std::istream& operator>>(std::istream& is, coord& coo);
	void convert() { this->x -= ('A' - 1); }//EZ az asciit int értékére váltja
};

std::istream& operator>>(std::istream& is, coord& coo) {
	char first;
	int second;
	is >> first >> second;
	first = std::toupper(first);
	if (first >= 'A' && first <= 'H' && second >= 1 && second <= 8) {
		coo.x = first - 'A' + 1;
		coo.y = second;
		return is;
	}
}

class bstep{
	coord start;
	coord end;
public: 
	//lépés hossza a nagyobb különbség a koordinátákból
	int lenght() {
		if ((end.getx() - start.getx()) >= (end.gety() - start.gety()))
			return end.getx() - start.gety();
		else return end.gety() - start.gety();
	}
	bool isYdir() { return !(end.getx() - start.getx()); }
	bool isXdir() { return !(end.gety() - start.gety()); }
	bool isdiag() {
		return ((end.getx() - start.getx()) == (end.gety() - start.gety()));
	}
	friend std::istream& operator>>(std::istream& is, bstep& s);
};
std::istream& operator>>(std::istream& is, bstep& s)
{
	is >>this->start>>this->end;
}