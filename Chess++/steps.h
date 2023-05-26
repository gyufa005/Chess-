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
	step() { valid = false };
	bool valid;
public:
	//koordinátákból stringbe, és vissza.
	void makemove() { move[] = { cords[0] + 'A' - 1,cords[1] + '0',cords[2] + 'A' - 1,cords[3] + '0'}; return; }
	void makecords() {cords[0] = move[0] - 'A' + 1; cords[1] = move[1] - '0'; cords[2] = move[2] - 'A' + 1; cords[3] = move[3] - '0'; return; }
	//getter,setter
	int& getcords()const { return cords; }
	string& getmove()const { return move; }
	void setmove(char* input) { move = input; }
	//beolvasás stringként
	friend istream& operator>>(istream& is);
	friend ostream& operator<<(ostream& os,const step& s);

	//random függvények amik kellhetnek
	bool isdiag() { return((cords[2] - cords[0]) == cords[3] - cords[1]); }
	bool isstraight() { return((cords[2] == cords[0]) || (cords[3]) == cords[1]; }
	bool isforwardbackward() { return cords[2] == cords[0]; }
	int length(){return }
};
istream& operator>>(istream& is)
{
	static step s;
	is >> s.move;
	//a hossz és tartomány tesztelése
	if(strlen(s.move)==4&&((s.move[0]<='H'&&s.move[0]>='A')||(s.move[0]<='h'&&s.move[0]>='a')&& 
	(s.move[2] <= 'H' && s.move[2] >= 'A') || (s.move[2] <= 'h' && s.move[2] >= 'a')&&
	(s.move[1] <= '8' && s.move[1] >= '1')
	(s.move[3] <= '8' && s.move[3] >= '1'))
	s.makecords();
	else
	cout<<"\nHelytelen lepes formatum.\n";
}
ostream& operator<<(ostream& os, step& s)
{
	makemove();
	os << move<<endl;
}