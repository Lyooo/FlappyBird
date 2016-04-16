#include "draw.h"

void Draw::GotoXY(const COORD & site)
{
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), site);
}

void Draw::DrawCowOnTheScreen(const Object::RangeType & xRange, SHORT y, char s)
{
	for (auto x = xRange.first; x <= xRange.second; ++x)
	{
		GotoXY({ x, y });
		std::cout << s;
	}
}

void Draw::DrawColumnOnTheScreen(const Object::RangeType & yRange, SHORT x, char s)
{
	for (auto y = yRange.first; y <= yRange.second; ++y)
	{
		GotoXY({ x, y });
		std::cout << s;
	}
}

void Draw::DrawObjectOnTheScreen(const Object::ObjectSite & o, char s, const Object::RangeType & xOutOfRange)
{
	for (auto x = o.xRange.first; x <= o.xRange.second; ++x)
	{
		if (x <= xOutOfRange.first || x >= xOutOfRange.second)
		{
			continue;
		}
		DrawColumnOnTheScreen(o.yRange, x, s);
	}
}