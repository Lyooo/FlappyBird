/************************************************************/
/* */

#pragma once

#include <utility>
#include "functions.h"

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
	// 表示一个范围
	// pair.first为线段的起点，pair.second为线段的终点
	using RangeType = std::pair<SHORT, SHORT>;

	// 表示一个方块的具体位置
	// pair.first为X的范围，pair.second为Y的范围
	using ObjectSite = std::pair<RangeType, RangeType>;

	Object() = delete;
	Object(const ObjectSite& o, char s);
	Object(ObjectSite&& o, char s);
	Object(const RangeType& x, const RangeType& y, char s);
	Object(const Object& other) = default;
	Object& operator= (const Object& other) = default;
	~Object() = default;

	// 根据方向平移物体一格，并且在屏幕上移动物体
	void MovedParallel(MOVEDIR::TYPE dir);

	// 根据方向平移物体一格，并且在屏幕上移动物体
	// 打印时超出axisRangeX范围不打印
	void MovedParallel(MOVEDIR::TYPE dir, const RangeType& axisRangeX);

	// 返回X轴方向的范围
	const RangeType& RangeX() const;

	// 返回y轴方向的范围
	const RangeType& RangeY() const;

	// 判断两个物体是否相撞
	friend bool Collision(
		const Object& a, const Object& b);

	// 在屏幕上打印物体
	friend void DrawObjectOnTheScreen(
		const Object& o);

	// 在屏幕上打印物体，X轴方向超出axisRangeX范围不打印
	friend void DrawObjectOnTheScreen(
		const Object& o, const RangeType& axisRangeX);

	// 根据移动后的物体位置以及移动方向，在屏幕上移动物体
	friend void MovedObjectInTheScreen(
		const Object& moveAfter, MOVEDIR::TYPE dir);

	// 根据移动后的物体位置以及移动方向，在屏幕上移动物体
	// X轴方向超出axisRangeX范围不打印
	friend void MovedObjectInTheScreen(
		const Object& moveAfter, MOVEDIR::TYPE dir,
		const RangeType& axisRangeX);

private:
	// 物体的位置
	ObjectSite obj;
	// 物体的符号
	char symbol;
};

bool Collision(const Object& a, const Object& b);
void DrawObjectOnTheScreen(const Object& o);
void DrawObjectOnTheScreen(const Object& o, const Object::RangeType& axisRangeX);
void MovedObjectInTheScreen(const Object& moveAfter, MOVEDIR::TYPE dir);
void MovedObjectInTheScreen(const Object& moveAfter, MOVEDIR::TYPE dir,
	const Object::RangeType& axisRangeX);