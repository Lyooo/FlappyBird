/*******************************************************/
/*         一个Obstacle包含了一系列的墙和4个边界         */
/******************************************************/

#pragma once

#ifndef _OBSTACLE_
#define _OBSTACLE_

#include "object.h"
#include <deque>
#include <vector>
#include <random>

class Obstacle
{
public:
	// 一个墙可以看成两个Object的集合
	// pair.first为上部分，pair.second为下部分
	using WALL = std::pair<Object, Object>;

	Obstacle() = delete;
	Obstacle(
		const Object::RangeType& bX, // 设定X轴的边界
		const Object::RangeType& bY, // 设定Y轴的边界
		SHORT ww,                    // 设定墙的宽度
		SHORT wgh,                   // 设定墙上缺口的高度，必须小于bY的一半
		SHORT d,                     // 设定墙与墙之间的距离
		char ws,                     // 设定墙的符号
		char bs                      // 设定边界的符号
	);

	// 所有墙都左移distance格
	void MovingAllWall(MOVEDIR::TYPE dir, SHORT distance);

	// 检测一个物体obj与所有墙，边界是否有碰撞
	bool CollisionWithTheWalls(const Object& obj) const;

	// 检测一个物体obj与所有墙，边界是否有碰撞
	// 若有墙通过鸟的位置，score增加
	bool CollisionWithTheWalls(const Object& obj, int& score) const;

private:

	// 需要时生成新墙到walls
	void BuildNewWall();
	
	// 需要时删除超出边界的墙，（walls.front()）
	void DeleteUnusefulWall();

	// 从左往右墙的队列，先进先出
	std::deque<WALL> walls;

	// 上下左右边界为4个Object
	std::vector<Object> boundaryWalls;

	// 边界X的区间 [first, second]
	Object::RangeType boundaryRangeX;

	// 边界Y的区间 [first, second]
	Object::RangeType boundaryRangeY;

	// 墙的宽
	SHORT wallWidth;

	// 墙上缺口的高度
	SHORT wallGapHight;

	// 墙与墙之间的间距
	SHORT distance;

	// 墙的符号
	char wallSymbol;

	// 边界的符号
	char boundarySymbol;

	// 随机生成器，生成墙缺口的位置
	std::default_random_engine e;
	std::uniform_int_distribution<SHORT> u;
};

#endif // !_OBSTACLE_