
#include <string>
#include <stdio.h>
#include <iostream>
//#include "steps.h"
#include "alternatesteps.h"
#include "pieces.h"
#include <iostream>
#include <stdio.h>
#include "altboard.h"
void erase()
{
	for (int i = 0; i < 28; i++)
		printf("\n");
}
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
	if (f->getC() - b.turncolour() == 0)
	{
		if (f->canitmove(s))
		{
			if (b.checkmove(s))
				return true;
		}
		else throw "the piece cannot move like that";
	}
	else
		throw "incorrect color. pick another piece.";
	return false;
}
void game(altboard& b) {
	bool gameend = false;
	while (!gameend)
	{
		step s;
		try {
			std::cin >> s;
			if (teststep(s, b))
			{
				b.doMove(s);
				erase();
				b.drawboard();
				if (b.wincond_check())
					gameend = true;
			}

		}
		catch (const char* errmsg) { std::cerr << "Error: " << errmsg << std::endl; }
	}
}


int main()
{
	altboard b;
	char k;
	b.drawboard();
	game(b);
	if (b.whowon())
		std::cout << "White won, congrats" << std::endl;
	else
		std::cout << "Black won, congrats" << std::endl;
	return 0;
}
