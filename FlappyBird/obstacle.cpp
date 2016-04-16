#include "obstacle.h"
#include "draw.h"
#include <ctime>

Obstacle::Obstacle(
	const Object::RangeType& bX, const Object::RangeType& bY,
	SHORT ww, SHORT wgh, SHORT d, char ws, char bs)
	: boundaryRangeX(bX), boundaryRangeY(bY), wallWidth(ww),
	wallGapHight(wgh), distance(d), wallSymbol(ws), boundarySymbol(bs),
	e(static_cast<unsigned>(time(0))), // 设定随机生成器种子
	u(
		bY.first + (bY.second - bY.first) / 8, // 缺口上部分可以最上的y坐标
		bY.second - (bY.second - bY.first) / 8 - wgh // 缺口上部分可以最下的y坐标
	)
{
	// 上下左右边界
	boundaryWalls.push_back({ 
		boundaryRangeX, 
		{ boundaryRangeY.first, boundaryRangeY.first },
		boundarySymbol 
	});
	boundaryWalls.push_back({
		boundaryRangeX,
		{ boundaryRangeY.second, boundaryRangeY.second },
		boundarySymbol
	});
	boundaryWalls.push_back({
		{ boundaryRangeX.first, boundaryRangeX.first },
		boundaryRangeY,
		boundarySymbol
	});
	boundaryWalls.push_back({
		{ boundaryRangeX.second, boundaryRangeX.second },
		boundaryRangeY,
		boundarySymbol
	});

	// 打印边界
	for (const auto& m : boundaryWalls)
	{
		Draw::DrawObjectOnTheScreen(m.Site(), m.Symbole());
	}

	// 建造第一个墙
	BuildNewWall();
}

void Obstacle::MovingAllWall(MOVEDIR::TYPE dir, SHORT distance)
{
	for (auto& m : walls)
	{
		m.first.MovedParallel(dir, distance, boundaryRangeX);
		m.second.MovedParallel(dir, distance, boundaryRangeX);
	}

	BuildNewWall();
	DeleteUnusefulWall();
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

bool Obstacle::CollisionWithTheWalls(const Object& obj, int& score) const
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
	if (walls.empty() || // 如果没有墙
		                 // 或与最右边的墙距离足够时建立新墙
		walls.back().first.RangeX().second < boundaryRangeX.second - distance)
	{
		// 缺口y.first
		auto temp = u(e);

		// 墙的上部分
		Object upperWall(
		{ boundaryRangeX.second, boundaryRangeX.second + wallWidth - 1 },
		{ boundaryRangeY.first + 1, temp },
			wallSymbol
		);

		// 墙的下部分
		Object bottomWall(
		{ boundaryRangeX.second, boundaryRangeX.second + wallWidth - 1 },
		{ temp + wallGapHight, boundaryRangeY.second - 1 },
			wallSymbol
		);

		walls.push_back({ upperWall, bottomWall });
	}
}

void Obstacle::DeleteUnusefulWall()
{ 
	// 最左边的墙超出左边界时删除
	if (walls.front().first.RangeX().second < boundaryRangeX.first)
	{
		walls.pop_front();
	}
}