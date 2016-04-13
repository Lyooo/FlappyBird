// 障碍物由墙和边界组成
// 根据墙的位置自动生成新墙或移除不在画面内的墙
// 墙的缺口位置随机生成

#pragma once

#include "time_control.h"
#include "object.h"
#include <deque>
#include <vector>
#include <random>

class Obstacle
{
public:
	// 一个移动的墙由上下两部分组成
	// pair.first为上部分，pair.second为下部分
	using WALL = std::pair<Object, Object>;

	Obstacle() = delete;
	Obstacle(
		const std::pair<Object::RangeType, Object::RangeType>& b,
		SHORT w, SHORT wgh, SHORT d, char s = '#');

	// 所有墙都左移一格
	void MovingAllWall(MOVEDIR::TYPE dir);

	// 检测一个物体obj与所有墙，边界是否有碰撞
	bool CollisionWithTheWalls(const Object& obj) const;

	// 检测一个物体obj与所有墙，边界是否有碰撞
	// 若有墙通过鸟的位置，score增加
	bool CollisionWithTheWalls(const Object& obj, int& score) const;

private:
	// 若需要生成新墙，就在在最右侧边界建造一个新墙
	void BuildNewWall();
	
	// 若最左的墙完全超出边界，删除
	void DeleteFirstWall();

	// 墙的集合
	std::deque<WALL> walls;

	// 边界的集合
	std::vector<Object> boundaryWalls;

	// 边界的X，Y范围
	std::pair<Object::RangeType, Object::RangeType> boundary;

	// 可移动墙的宽
	SHORT wallWidth;

	// 可移动墙的缺口高度
	SHORT wallGapHight;

	// 墙与墙之间的间距
	SHORT distance;

	// 可移动墙的符号
	char symbol;

	// 随机生成器，生成墙缺口的位置
	std::default_random_engine e;
	std::uniform_int_distribution<SHORT> u;
};