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
	// pair.firstΪx��ƫ������ pair.secondΪy���ƫ����
	using TYPE = std::pair<SHORT, SHORT>;
	
	// ��ĳ�������ƶ�һ��
	const static TYPE RISE({ 0, -1 });
	const static TYPE FALL({ 0, 1 });
	const static TYPE BACKWARD({ -1, 0 });
}

class Object
{
public:
	// ��ʾһ������
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

		// ��������λ�õ�x���䣬�պ����� -> [a, b]
		RangeType xRange;

		// ��������λ�õ�y����
		RangeType yRange;
	};

	Object() = delete;
	Object(const ObjectSite& o, char s);
	Object(const RangeType& x, const RangeType& y, char s);
	Object(const Object&) = default;
	Object& operator= (const Object&) = default;
	~Object() = default;

	// ��dir�����ƶ�distance��
	// x�᷽�򳬳�xOutOfRange��Χ����ӡ
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