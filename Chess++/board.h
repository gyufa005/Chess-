#pragma once
#include <iostream>
/* unicode bábuk: 
	fehér:  ♜♞♝♛♚♟︎
	fekete: ♖♘♗♕♔♙
	morph bábu: fekete: m,fehér: M
*/
	static class board {
		//gyakran előfordulhatnak ezek a karakterek: 
#define whitesquare 0xDB
#define blacksquare 0xFF
#define zero 0x20
		typedef unsigned int uint;
		enum { empty =0 , bishop=1, tower=2, queen=3, rook=4, morph=5, pawn = 6};
		static char** boardcontents;
		const int size=8;
		/*
				{ '♜', '♚', '♝', '♛', '♚', '♝', '♚', '♜' },
				{ '♟︎',  '♟︎',  'M',  '♟︎',  '♟︎',  'M',  '♟︎','♟'},
				{ zero, zero, zero, zero, zero, zero, zero, zero },
				{ zero, zero, zero, zero, zero, zero, zero, zero },
				{ zero, zero, zero, zero, zero, zero, zero, zero },
				{ zero, zero, zero, zero, zero, zero, zero, zero },
				{ '♙',  '♙',  'm',  '♙',  '♙',  'm',  '♙',  '♙' },
				{ '♖',  '♔',  '♗',  '♕',  '♔',  '♗',  '♔',  '♖' } };*/
		board();
		~board();
	public:
		static board& getboard() { static board b; return b;}
		static void drawboard();
	};
