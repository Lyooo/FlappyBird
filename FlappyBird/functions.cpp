#include "functions.h"

void GotoXY(const COORD& site)
{
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), site);
}

void DrawHorizontal(const COORD& begin, SHORT endX, char s)
{
	for (auto x = begin.X; x <= endX; ++x)
	{
		GotoXY({ x, begin.Y });
		std::cerr << s;
	}
}

void DrawVertical(const COORD& begin, SHORT endY, char s)
{
	for (auto y = begin.Y; y <= endY; ++y)
	{
		GotoXY({ begin.X, y });
		std::cerr << s;
	}
}