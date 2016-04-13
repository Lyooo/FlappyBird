// �ϰ�����ǽ�ͱ߽����
// ����ǽ��λ���Զ�������ǽ���Ƴ����ڻ����ڵ�ǽ
// ǽ��ȱ��λ���������

#pragma once

#include "time_control.h"
#include "object.h"
#include <deque>
#include <vector>
#include <random>

class Obstacle
{
public:
	// һ���ƶ���ǽ���������������
	// pair.firstΪ�ϲ��֣�pair.secondΪ�²���
	using WALL = std::pair<Object, Object>;

	Obstacle() = delete;
	Obstacle(
		const std::pair<Object::RangeType, Object::RangeType>& b,
		SHORT w, SHORT wgh, SHORT d, char s = '#');

	// ����ǽ������һ��
	void MovingAllWall(MOVEDIR::TYPE dir);

	// ���һ������obj������ǽ���߽��Ƿ�����ײ
	bool CollisionWithTheWalls(const Object& obj) const;

	// ���һ������obj������ǽ���߽��Ƿ�����ײ
	// ����ǽͨ�����λ�ã�score����
	bool CollisionWithTheWalls(const Object& obj, int& score) const;

private:
	// ����Ҫ������ǽ�����������Ҳ�߽罨��һ����ǽ
	void BuildNewWall();
	
	// �������ǽ��ȫ�����߽磬ɾ��
	void DeleteFirstWall();

	// ǽ�ļ���
	std::deque<WALL> walls;

	// �߽�ļ���
	std::vector<Object> boundaryWalls;

	// �߽��X��Y��Χ
	std::pair<Object::RangeType, Object::RangeType> boundary;

	// ���ƶ�ǽ�Ŀ�
	SHORT wallWidth;

	// ���ƶ�ǽ��ȱ�ڸ߶�
	SHORT wallGapHight;

	// ǽ��ǽ֮��ļ��
	SHORT distance;

	// ���ƶ�ǽ�ķ���
	char symbol;

	// ���������������ǽȱ�ڵ�λ��
	std::default_random_engine e;
	std::uniform_int_distribution<SHORT> u;
};