/*********** ��Ϸ��FlappyBird�� **********/
/*********** ������2016��04��08 **********/
/*********** �����2016��04��09 **********/
/*********** 2016��04��11�����޸� ********/

#include "time_control.h"
#include "obstacle.h"
#include "draw.h"
#include <Windows.h>
#include <iostream>

void BeginScreen()
{
	system("cls");
	std::cout << "Press \"UP\" To Let Bird Rise." << std::endl
		<< "Press \"UP\" To Continue." << std::endl;
	while (!(GetAsyncKeyState(38) && 0x8000));
	system("cls");
}

void ScoreScreen(const COORD& scoreSite, int score)
{
	Draw::GotoXY(scoreSite);
	std::cout << "SCORE: " << score << "." << std::endl;
}

bool DeadScreen(int score)
{
	Sleep(500);
	system("cls");

	std::cout << "**** YOU DIE! ****" << std::endl
		<< "You score is " << score << std::endl
		<< "Press \"RIGHT\" To Play Again." << std::endl
		<< "Press \"LEFT\" To Exit." << std::endl;
	
	while (true)
	{
		if (GetAsyncKeyState(39) && 0x8000)
		{
			return true;
		}
		if (GetAsyncKeyState(37) && 0x8000)
		{
			return false;
		}
	}
}

int main()
{
	for (BeginScreen(); ; BeginScreen()) // ��Ϸ��ѭ��
	{
		// �߿��X��Χ
		Object::RangeType frameX({ 0,35 });
		// �߿��Y��Χ
		Object::RangeType frameY({ 0,25 });

		// ��ĳ�ʼλ��
		Object::ObjectSite birdSite({ 10,12 }, { 7,8 });
		// ��ķ���
		char birdSymbol = '&';

		// ǽ�Ŀ��
		SHORT wid = 6;
		// ȱ�ڵĸ߶�
		SHORT hig = 7;
		// ǽ�ļ��
		SHORT dis = 10;
		// ǽ�ķ���
		char wallSymbol = '#';
		//
		char boundarySymbol = '%';

		// ����
		int score = 0;
		// ����λ��
		const COORD scoreSite = { 1,27};
		ScoreScreen(scoreSite, score);

		Obstacle obs(frameX, frameY, wid, hig, dis, wallSymbol, boundarySymbol);

		Object bird(birdSite, birdSymbol);
		Draw::DrawObjectOnTheScreen(bird.Site(), bird.Symbole());

		// ǽ�ƶ��ƶ�һ���ʱ����
		TimeControl wallMoveTime({ 150 });
		// �������ƶ�һ���ʱ����
		TimeControl birdUp({ 50, 90, 140 });
		// �������ƶ�һ���ʱ����
		TimeControl birdDown({ 150,110,90,70,60 });

		Sleep(1000);

		// ������ѭ��
		for (birdUp.SetEnd(), birdDown.Reset(), wallMoveTime.Reset() // ���ʼΪ����״̬
			;;)
		{
			if (birdDown.TimeTargetComplete()) // �ж����Ƿ���Ҫ����
			{
				bird.MovedParallel(MOVEDIR::FALL);

				if (obs.CollisionWithTheWalls(bird)) // �ж��ƶ����Ƿ���ײ
				{
					if (DeadScreen(score))
					{
						break;
					}
					else
					{
						return 0;
					}
				}

				// ����ѵ������һ��ʱ����������ʹ�����ʱ����
				if (birdDown.ControlEnd())
				{
					birdDown.ResetToLastInterval();
				}
			}
			else if (birdUp.TimeTargetComplete()) // �ж����Ƿ���Ҫ����
			{
				bird.MovedParallel(MOVEDIR::RISE);

				if (obs.CollisionWithTheWalls(bird))
				{
					if (DeadScreen(score))
					{
						break;
					}
					else
					{
						return 0;
					}
				}

				// ������������㣬��ʼ����
				if (birdUp.ControlEnd())
				{
					birdDown.Reset();
				}
			}

			// ����������ʱ����ʼ����
			if (GetAsyncKeyState(38) && 0x8000)
			{
				birdDown.SetEnd();
				birdUp.Reset();
			}

			// �ж�ǽ�Ƕ���Ҫ�ƶ�
			if (wallMoveTime.TimeTargetComplete())
			{
				obs.MovingAllWall(MOVEDIR::BACKWARD, 1);

				if (obs.CollisionWithTheWalls(bird, score))
				{
					// ǿ�����λ��
					Draw::DrawObjectOnTheScreen(bird.Site(), bird.Symbole());

					if (DeadScreen(score))
					{
						break;
					}
					else
					{
						return 0;
					}
				}

				ScoreScreen(scoreSite, score);

				if (wallMoveTime.ControlEnd())
				{
					wallMoveTime.Reset();
				}
			}
		}
	}
}