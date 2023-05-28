#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;
class step {
	//A lépés stringként, és külön számokként is kezelhető
	//! A tábla osztálhoz képest a megadott koordináták fordítva lesznek.
	int cords[4];
	string move;
	bool valid;
public:
	step() :valid(false) {}
	//koordinátákból stringbe, és vissza.
	void makemove() {
		move = string(1, cords[0] + 'A' - 1) + to_string(cords[1]) + string(1, cords[2] + 'A' - 1) + to_string(cords[3]);
	}
	void makecords() {cords[0] = move[0] - 'A' + 1; cords[1] = move[1] - '0'; cords[2] = move[2] - 'A' + 1; cords[3] = move[3] - '0'; return; }
	//getter,setter
	const int& getcords()const { return cords; }
	const string& getmove()const { return move; }
	void setmove(char* input) { move = input; }
	//beolvasás stringként
	friend istream& operator>>(istream& is,static step& s);
	friend ostream& operator<<(ostream& os,const step& s);

	//random függvények amik kellhetnek
	bool isdiag() { return((cords[2] - cords[0]) == cords[3] - cords[1]); }
	bool isstraight() { return((cords[2] == cords[0]) || (cords[3]) == cords[1]); }
	bool isforwardbackward() { return cords[2] == cords[0]; }
	int distance() { if ((cords[2] - cords[0]) >= (cords[3] - cords[1]))return cords[2] - cords[0]; else return cords[3] - cords[1]; }
};
istream& operator>>(istream& is,static step& s)
{
	is >> s.move;
	//a hossz és tartomány tesztelése
	if (strlen(s.move) == 4 && ((s.move[0] <= 'H' && s.move[0] >= 'A') || (s.move[0] <= 'h' && s.move[0] >= 'a') &&
		(s.move[2] <= 'H' && s.move[2] >= 'A') || (s.move[2] <= 'h' && s.move[2] >= 'a') &&
		(s.move[1] <= '8' && s.move[1] >= '1')
		(s.move[3] <= '8' && s.move[3] >= '1'))) {
		s.makecords();
	}
	else
	cout<<"\nHelytelen lepes formatum.\n";
return is;
}
ostream& operator<<(ostream& os,const step& s)
{
	os << s.getmove()<<endl;
	return os;
}