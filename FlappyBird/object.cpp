#include "object.h"

Object::Object(const ObjectSite& o, char s) : obj(o), symbol(s)
{ }

Object::Object(ObjectSite&& o, char s) : obj(std::move(o)), symbol(s)
{ }

Object::Object(const RangeType& x, const RangeType& y, char s)
	: Object({ x,y }, s)
{ }

void Object::MovedParallel(MOVEDIR::TYPE dir)
{
	obj.first.first += dir.first;
	obj.first.second += dir.first;
	obj.second.first += dir.second;
	obj.second.second += dir.second;

	MovedObjectInTheScreen(*this, dir);
}

void Object::MovedParallel(MOVEDIR::TYPE dir, const RangeType& axisRangeX)
{
	obj.first.first += dir.first;
	obj.first.second += dir.first;
	obj.second.first += dir.second;
	obj.second.second += dir.second;

	MovedObjectInTheScreen(*this, dir, axisRangeX);
}

const Object::RangeType& Object::RangeX() const
{
	return obj.first;
}

const Object::RangeType& Object::RangeY() const
{
	return obj.second;
}

bool Collision(const Object& a, const Object& b)
{
	// 长方形重叠问题
	if (a.obj.first.first <= b.obj.first.second &&
		a.obj.first.second >= b.obj.first.first &&
		a.obj.second.first <= b.obj.second.second &&
		a.obj.second.second >= b.obj.second.first)
	{
		return true;
	}
	return false;
}

void DrawObjectOnTheScreen(const Object& o)
{
	for (auto x = o.obj.first.first; x <= o.obj.first.second; ++x)
	{
		DrawVertical(
		{ x, o.obj.second.first }, o.obj.second.second, o.symbol);
	}
}

void DrawObjectOnTheScreen(
	const Object& o, const Object::RangeType& axisRangeX)
{
	for (auto x = o.obj.first.first; x <= o.obj.first.second; ++x)
	{
		if (x <= axisRangeX.first || x >= axisRangeX.second)
		{
			continue;
		}
		DrawVertical(
		{ x, o.obj.second.first }, o.obj.second.second, o.symbol);
	}
}

void MovedObjectInTheScreen(const Object& moveAfter, MOVEDIR::TYPE dir)
{
	if (dir == MOVEDIR::RISE)
	{
		DrawHorizontal(
		{ moveAfter.obj.first.first, moveAfter.obj.second.first },
			moveAfter.obj.first.second, moveAfter.symbol);
		DrawHorizontal(
		{ moveAfter.obj.first.first, moveAfter.obj.second.second + 1 },
			moveAfter.obj.first.second, ' ');
	}
	else if (dir == MOVEDIR::FALL)
	{
		DrawHorizontal(
		{ moveAfter.obj.first.first, moveAfter.obj.second.second },
			moveAfter.obj.first.second, moveAfter.symbol);
		DrawHorizontal(
		{ moveAfter.obj.first.first, moveAfter.obj.second.first - 1 },
			moveAfter.obj.first.second, ' ');
	}
	else if (dir == MOVEDIR::BACKWARD)
	{
		DrawVertical(
		{ moveAfter.obj.first.first, moveAfter.obj.second.first },
			moveAfter.obj.second.second, moveAfter.symbol);
		DrawVertical(
		{ moveAfter.obj.first.second + 1, moveAfter.obj.second.first },
			moveAfter.obj.second.second, ' ');
	}
}

void MovedObjectInTheScreen(
	const Object& moveAfter, MOVEDIR::TYPE dir,
	const Object::RangeType& axisRangeX)
{
	if (dir == MOVEDIR::RISE)
	{
		DrawHorizontal(
		{ moveAfter.obj.first.first, moveAfter.obj.second.first },
			moveAfter.obj.first.second, moveAfter.symbol);
		DrawHorizontal(
		{ moveAfter.obj.first.first, moveAfter.obj.second.second + 1 },
			moveAfter.obj.first.second, ' ');
	}
	else if (dir == MOVEDIR::FALL)
	{
		DrawHorizontal(
		{ moveAfter.obj.first.first, moveAfter.obj.second.second },
			moveAfter.obj.first.second, moveAfter.symbol);
		DrawHorizontal(
		{ moveAfter.obj.first.first, moveAfter.obj.second.first - 1 },
			moveAfter.obj.first.second, ' ');
	}
	else if (dir == MOVEDIR::BACKWARD)
	{
		if (moveAfter.obj.first.first > axisRangeX.first &&
			moveAfter.obj.first.first < axisRangeX.second)
		{
			DrawVertical(
			{ moveAfter.obj.first.first, moveAfter.obj.second.first },
				moveAfter.obj.second.second, moveAfter.symbol);
		}
		if (moveAfter.obj.first.second + 1 > axisRangeX.first &&
			moveAfter.obj.first.second + 1 < axisRangeX.second)
		{
			DrawVertical(
			{ moveAfter.obj.first.second + 1, moveAfter.obj.second.first },
				moveAfter.obj.second.second, ' ');
		}
	}
}