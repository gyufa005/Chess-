#include <iostream>
#include <string>
#include <stdio.h>
#include "board.h"
//#include "steps.h"
#include "alternatesteps.h"
#include "pieces.h"
#include <iostream>
#include <stdio.h>
#include "altboard.h"
bool teststep(const step& s, const altboard& b)
{
	//! A függvény megnézi, hogy a bábu amivel lépni szeretne helyes színű, 
	//! és tud olyat lépni, majd megnézi nem áll-e az útjában másik bábu.
	piece* f;
	piece* t;
	coord start = s.getstart();
	coord end = s.getend();
	f = b.at(start);
	t = b.at(end);
	if (f->getC() == b.turncolour())
	{
		if (f->canitmove(s))
			if (b.checkmove(s))
				return true;
	}
	else return false;
}
int game(const altboard& b){
	bool gameend = false;
	while (!gameend)
	{
		step s;
		try {
			std::cin >> s;
			teststep(s,b);
		}
		catch (const char* errmsg) { std::cerr << "Error: " << errmsg << std::endl; }
	}
}

void erase()
{
	for (int i = 0; i < 28; i++)
		printf("\n");
}
int main()
{
	altboard b;
	char k;
	b.drawboard();
	scanf_s("%c",&k);
	erase();
	b.drawboard();
	step s;
	std::cin >> s;
	//piece(s.)
	return 0;
}