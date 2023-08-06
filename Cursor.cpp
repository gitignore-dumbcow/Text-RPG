#include "Cursor.h"

void Cursor::gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	std::cout.flush();
	SetConsoleCursorPosition(GetStdHandle(STD_INPUT_HANDLE), coord);
}
