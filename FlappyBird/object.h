/************************************************************/
/* */
/************************************************************/

#pragma once

#ifndef _OBJECT_
#define _OBJECT_

#include <utility>
#include <Windows.h>

namespace MOVEDIR
{
	// pair.first为x轴偏移量， pair.second为y轴的偏移量
	using TYPE = std::pair<SHORT, SHORT>;
	
	// 往某个方向移动一格
	const static TYPE RISE({ 0, -1 });
	const static TYPE FALL({ 0, 1 });
	const static TYPE BACKWARD({ -1, 0 });
}

class Object
{
public:
	// 表示一个区间
	// [pair.first, pair.second]
	using RangeType = std::pair<SHORT, SHORT>;

	class ObjectSite
	{
	public:
		ObjectSite() = default;
		ObjectSite(const RangeType& x, const RangeType&y)
			: xRange(x), yRange(y){ }
		ObjectSite(const ObjectSite&) = default;
		ObjectSite& operator= (const ObjectSite&) = default;

		// 物体所在位置的x区间，闭合区间 -> [a, b]
		RangeType xRange;

		// 物体所在位置的y区间
		RangeType yRange;
	};

	Object() = delete;
	Object(const ObjectSite& o, char s);
	Object(const RangeType& x, const RangeType& y, char s);
	Object(const Object&) = default;
	Object& operator= (const Object&) = default;
	~Object() = default;

	// 往dir方向移动distance格
	// x轴方向超出xOutOfRange范围不打印
	void MovedParallel(
		MOVEDIR::TYPE dir, SHORT distance = 1,
		const RangeType& xOutOfRange = { -1, MAXSHORT });

	const RangeType& RangeX() const;

	const RangeType& RangeY() const;

	const ObjectSite& Site() const;

	char Symbole() const;

	friend bool Collision(
		const Object& a, const Object& b);

private:
	ObjectSite objSite;
	char symbol;
};

bool Collision(const Object& a, const Object& b);

#endif // !_OBJECT_