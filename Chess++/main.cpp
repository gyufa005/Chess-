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
	piece* p;
	coord start = s.getstart();
	coord end = s.getend();
	p = b.at(start);
	if (p->getC() == b.turncolour());
	p.canitmove(s);
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