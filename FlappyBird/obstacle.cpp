#include "obstacle.h"
#include "draw.h"

Obstacle::Obstacle(
	const std::pair<Object::RangeType, Object::RangeType>& b,
	SHORT w, SHORT wgh, SHORT d, char s)
	: boundary(b), wallWidth(w), wallGapHight(wgh), distance(d), symbol(s),
	e(static_cast<unsigned>(time(0))),
	u(b.second.first + 3,
		b.second.second - (wgh % (b.second.second - b.second.first - 3)) - 2)
	// u(a,b) 随机生成墙的缺口在Y轴的起点，
	// （u(a,b) + 缺口高度）就是缺口在Y轴的终点
{
	// 上下左右边界
	boundaryWalls.push_back({
		{ boundary.first.first, boundary.first.second },
		{ boundary.second.first, boundary.second.first }, '@' });
	boundaryWalls.push_back({
		{ boundary.first.first, boundary.first.first },
		{ boundary.second.first, boundary.second.second }, '@' });
	boundaryWalls.push_back({
		{ boundary.first.first, boundary.first.second },
		{ boundary.second.second, boundary.second.second }, '@' });
	boundaryWalls.push_back({
		{ boundary.first.second, boundary.first.second },
		{ boundary.second.first, boundary.second.second }, '@' });

	// 打印边界
	for (const auto& m : boundaryWalls)
	{
		Draw::DrawObjectOnTheScreen(m.Site(), m.Symbole());
	}

	// 建造第一个墙
	BuildNewWall();
}

void Obstacle::MovingAllWall(MOVEDIR::TYPE dir)
{
	for (auto& m : walls)
	{
		m.first.MovedParallel(dir, 2, { boundary.first.first, boundary.first.second });
		m.second.MovedParallel(dir, 2, { boundary.first.first, boundary.first.second });
	}

	// 每次移动都检测是否需要生成/删除墙
	BuildNewWall();
	DeleteFirstWall();
}

bool Obstacle::CollisionWithTheWalls(const Object& obj) const
{
	// 检测是否与墙相撞
	for (const auto& m : walls)
	{
		if (Collision(m.first, obj) || 
			Collision(m.second, obj))
		{
			return true;
		}
	}

	// 检测是都与边界相撞
	for (const auto& m : boundaryWalls)
	{
		if (Collision(obj, m))
		{
			return true;
		}
	}
	return false;
}

bool Obstacle::CollisionWithTheWalls(const Object & obj, int & score) const
{
	// 检测是否与墙相撞
	for (const auto& m : walls)
	{
		if (Collision(m.first, obj) ||
			Collision(m.second, obj))
		{
			return true;
		}

		if (m.first.RangeX().second == obj.RangeX().second)
		{
			++score;
		}
	}

	// 检测是都与边界相撞
	for (const auto& m : boundaryWalls)
	{
		if (Collision(obj, m))
		{
			return true;
		}
	}
	return false;
}

void Obstacle::BuildNewWall()
{
	if (walls.empty() ||
		walls.back().first.RangeX().second < boundary.first.second - distance)
	{
		auto temp = u(e);

		// 墙的上部分
		Object upperWall(
		{ boundary.first.second, boundary.first.second + wallWidth - 1 },
		{ boundary.second.first + 1, temp - 1 },
		symbol);

		// 墙的下部分
		Object bottomWall(
		{ boundary.first.second, boundary.first.second + wallWidth - 1 },
		{ temp + wallGapHight, boundary.second.second - 1 },
		symbol);

		walls.push_back({ upperWall, bottomWall });
	}
}

void Obstacle::DeleteFirstWall()
{ 
	if (walls.front().first.RangeX().second < boundary.first.first)
	{
		walls.pop_front();
	}
}