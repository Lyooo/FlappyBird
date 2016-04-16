/*******************************************************/
/*         һ��Obstacle������һϵ�е�ǽ��4���߽�         */
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
	// һ��ǽ���Կ�������Object�ļ���
	// pair.firstΪ�ϲ��֣�pair.secondΪ�²���
	using WALL = std::pair<Object, Object>;

	Obstacle() = delete;
	Obstacle(
		const Object::RangeType& bX, // �趨X��ı߽�
		const Object::RangeType& bY, // �趨Y��ı߽�
		SHORT ww,                    // �趨ǽ�Ŀ��
		SHORT wgh,                   // �趨ǽ��ȱ�ڵĸ߶ȣ�����С��bY��һ��
		SHORT d,                     // �趨ǽ��ǽ֮��ľ���
		char ws,                     // �趨ǽ�ķ���
		char bs                      // �趨�߽�ķ���
	);

	// ����ǽ������distance��
	void MovingAllWall(MOVEDIR::TYPE dir, SHORT distance);

	// ���һ������obj������ǽ���߽��Ƿ�����ײ
	bool CollisionWithTheWalls(const Object& obj) const;

	// ���һ������obj������ǽ���߽��Ƿ�����ײ
	// ����ǽͨ�����λ�ã�score����
	bool CollisionWithTheWalls(const Object& obj, int& score) const;

private:

	// ��Ҫʱ������ǽ��walls
	void BuildNewWall();
	
	// ��Ҫʱɾ�������߽��ǽ����walls.front()��
	void DeleteUnusefulWall();

	// ��������ǽ�Ķ��У��Ƚ��ȳ�
	std::deque<WALL> walls;

	// �������ұ߽�Ϊ4��Object
	std::vector<Object> boundaryWalls;

	// �߽�X������ [first, second]
	Object::RangeType boundaryRangeX;

	// �߽�Y������ [first, second]
	Object::RangeType boundaryRangeY;

	// ǽ�Ŀ�
	SHORT wallWidth;

	// ǽ��ȱ�ڵĸ߶�
	SHORT wallGapHight;

	// ǽ��ǽ֮��ļ��
	SHORT distance;

	// ǽ�ķ���
	char wallSymbol;

	// �߽�ķ���
	char boundarySymbol;

	// ���������������ǽȱ�ڵ�λ��
	std::default_random_engine e;
	std::uniform_int_distribution<SHORT> u;
};

#endif // !_OBSTACLE_