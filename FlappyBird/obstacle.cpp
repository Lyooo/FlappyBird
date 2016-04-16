#include "obstacle.h"
#include "draw.h"
#include <ctime>

Obstacle::Obstacle(
	const Object::RangeType& bX, const Object::RangeType& bY,
	SHORT ww, SHORT wgh, SHORT d, char ws, char bs)
	: boundaryRangeX(bX), boundaryRangeY(bY), wallWidth(ww),
	wallGapHight(wgh), distance(d), wallSymbol(ws), boundarySymbol(bs),
	e(static_cast<unsigned>(time(0))), // �趨�������������
	u(
		bY.first + (bY.second - bY.first) / 8, // ȱ���ϲ��ֿ������ϵ�y����
		bY.second - (bY.second - bY.first) / 8 - wgh // ȱ���ϲ��ֿ������µ�y����
	)
{
	// �������ұ߽�
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

	// ��ӡ�߽�
	for (const auto& m : boundaryWalls)
	{
		Draw::DrawObjectOnTheScreen(m.Site(), m.Symbole());
	}

	// �����һ��ǽ
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
	// ����Ƿ���ǽ��ײ
	for (const auto& m : walls)
	{
		if (Collision(m.first, obj) || 
			Collision(m.second, obj))
		{
			return true;
		}
	}

	// ����Ƕ���߽���ײ
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
	// ����Ƿ���ǽ��ײ
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

	// ����Ƕ���߽���ײ
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
	if (walls.empty() || // ���û��ǽ
		                 // �������ұߵ�ǽ�����㹻ʱ������ǽ
		walls.back().first.RangeX().second < boundaryRangeX.second - distance)
	{
		// ȱ��y.first
		auto temp = u(e);

		// ǽ���ϲ���
		Object upperWall(
		{ boundaryRangeX.second, boundaryRangeX.second + wallWidth - 1 },
		{ boundaryRangeY.first + 1, temp },
			wallSymbol
		);

		// ǽ���²���
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
	// ����ߵ�ǽ������߽�ʱɾ��
	if (walls.front().first.RangeX().second < boundaryRangeX.first)
	{
		walls.pop_front();
	}
}