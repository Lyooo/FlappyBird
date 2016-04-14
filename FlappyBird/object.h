/************************************************************/
/* */

#pragma once

#include <utility>
#include "functions.h"

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
	// ��ʾһ����Χ
	// pair.firstΪ�߶ε���㣬pair.secondΪ�߶ε��յ�
	using RangeType = std::pair<SHORT, SHORT>;

	// ��ʾһ������ľ���λ��
	// pair.firstΪX�ķ�Χ��pair.secondΪY�ķ�Χ
	using ObjectSite = std::pair<RangeType, RangeType>;

	Object() = delete;
	Object(const ObjectSite& o, char s);
	Object(ObjectSite&& o, char s);
	Object(const RangeType& x, const RangeType& y, char s);
	Object(const Object& other) = default;
	Object& operator= (const Object& other) = default;
	~Object() = default;

	// ���ݷ���ƽ������һ�񣬲�������Ļ���ƶ�����
	void MovedParallel(MOVEDIR::TYPE dir);

	// ���ݷ���ƽ������һ�񣬲�������Ļ���ƶ�����
	// ��ӡʱ����axisRangeX��Χ����ӡ
	void MovedParallel(MOVEDIR::TYPE dir, const RangeType& axisRangeX);

	// ����X�᷽��ķ�Χ
	const RangeType& RangeX() const;

	// ����y�᷽��ķ�Χ
	const RangeType& RangeY() const;

	// �ж����������Ƿ���ײ
	friend bool Collision(
		const Object& a, const Object& b);

	// ����Ļ�ϴ�ӡ����
	friend void DrawObjectOnTheScreen(
		const Object& o);

	// ����Ļ�ϴ�ӡ���壬X�᷽�򳬳�axisRangeX��Χ����ӡ
	friend void DrawObjectOnTheScreen(
		const Object& o, const RangeType& axisRangeX);

	// �����ƶ��������λ���Լ��ƶ���������Ļ���ƶ�����
	friend void MovedObjectInTheScreen(
		const Object& moveAfter, MOVEDIR::TYPE dir);

	// �����ƶ��������λ���Լ��ƶ���������Ļ���ƶ�����
	// X�᷽�򳬳�axisRangeX��Χ����ӡ
	friend void MovedObjectInTheScreen(
		const Object& moveAfter, MOVEDIR::TYPE dir,
		const RangeType& axisRangeX);

private:
	// �����λ��
	ObjectSite obj;
	// ����ķ���
	char symbol;
};

bool Collision(const Object& a, const Object& b);
void DrawObjectOnTheScreen(const Object& o);
void DrawObjectOnTheScreen(const Object& o, const Object::RangeType& axisRangeX);
void MovedObjectInTheScreen(const Object& moveAfter, MOVEDIR::TYPE dir);
void MovedObjectInTheScreen(const Object& moveAfter, MOVEDIR::TYPE dir,
	const Object::RangeType& axisRangeX);