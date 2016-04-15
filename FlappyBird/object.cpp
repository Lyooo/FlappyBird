#include "object.h"
#include "draw.h"

void MovedObjectInTheScreen(
	const Object::ObjectSite& moveAfter, MOVEDIR::TYPE dir, SHORT distance,
	char s, const Object::RangeType& xOutOfRange)
{
	if (dir == MOVEDIR::RISE)
	{
		for (
			auto y = moveAfter.yRange.first, y2 = moveAfter.yRange.second;
			y - moveAfter.yRange.first < distance && y <= moveAfter.yRange.second;
			++y, --y2
			)
		{
			Draw::DrawCowOnTheScreen(moveAfter.xRange, y, s);
			Draw::DrawCowOnTheScreen(moveAfter.xRange, y2 + distance, ' ');
		}
	}
	else if (dir == MOVEDIR::FALL)
	{
		for (
			auto y = moveAfter.yRange.first, y2 = moveAfter.yRange.second;
			y - moveAfter.yRange.first < distance && y <= moveAfter.yRange.second;
			++y, --y2
			)
		{
			Draw::DrawCowOnTheScreen(moveAfter.xRange, y - distance, ' ');
			Draw::DrawCowOnTheScreen(moveAfter.xRange, y2, s);
		}
	}
	else if (dir == MOVEDIR::BACKWARD)
	{
		for (
			auto x = moveAfter.xRange.first;
			x <= moveAfter.xRange.second + distance;
			x++
			)
		{
			if (x <= xOutOfRange.first || x >= xOutOfRange.second)
			{
				continue;
			}
			if (x < moveAfter.xRange.first + distance &&
				x <= moveAfter.xRange.second)
			{
				Draw::DrawColumnOnTheScreen(moveAfter.yRange, x, s);
			}
			else if (x >= moveAfter.xRange.first + distance &&
				x > moveAfter.xRange.second)
			{
				Draw::DrawColumnOnTheScreen(moveAfter.yRange, x, ' ');
			}
		}
	}
}

Object::Object(const ObjectSite& o, char s) : objSite(o), symbol(s)
{ }

Object::Object(const RangeType& x, const RangeType& y, char s)
	: Object({ x,y }, s)
{ }

void Object::MovedParallel(
	MOVEDIR::TYPE dir, SHORT distance,
	const RangeType& xOutOfRange)
{
	objSite.xRange.first += dir.first * distance;
	objSite.xRange.second += dir.first * distance;
	objSite.yRange.first += dir.second * distance;
	objSite.yRange.second += dir.second * distance;

	MovedObjectInTheScreen(
		this->objSite, dir, distance, this->symbol, xOutOfRange);
}

const Object::RangeType& Object::RangeX() const
{
	return objSite.xRange;
}

const Object::RangeType& Object::RangeY() const
{
	return objSite.yRange;
}

const Object::ObjectSite& Object::Site() const
{
	return objSite;
}

char Object::Symbole() const
{
	return symbol;
}

bool Collision(const Object& a, const Object& b)
{
	// 长方形重叠问题
	if (a.objSite.xRange.first <= b.objSite.xRange.second &&
		a.objSite.xRange.second >= b.objSite.xRange.first &&
		a.objSite.yRange.first <= b.objSite.yRange.second &&
		a.objSite.yRange.second >= b.objSite.yRange.first)
	{
		return true;
	}
	return false;
}