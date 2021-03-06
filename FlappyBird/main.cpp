/*********** 游戏《FlappyBird》 **********/
/*********** 创建于2016，04，08 **********/
/*********** 完成于2016，04，09 **********/
/*********** 2016，04，11进行修改 ********/

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
	for (BeginScreen(); ; BeginScreen()) // 游戏大循环
	{
		// 边框的X范围
		Object::RangeType frameX({ 0,35 });
		// 边框的Y范围
		Object::RangeType frameY({ 0,25 });

		// 鸟的初始位置
		Object::ObjectSite birdSite({ 10,12 }, { 7,8 });
		// 鸟的符号
		char birdSymbol = '&';

		// 墙的宽度
		SHORT wid = 6;
		// 缺口的高度
		SHORT hig = 7;
		// 墙的间距
		SHORT dis = 10;
		// 墙的符号
		char wallSymbol = '#';
		//
		char boundarySymbol = '%';

		// 分数
		int score = 0;
		// 分数位置
		const COORD scoreSite = { 1,27};
		ScoreScreen(scoreSite, score);

		Obstacle obs(frameX, frameY, wid, hig, dis, wallSymbol, boundarySymbol);

		Object bird(birdSite, birdSymbol);
		Draw::DrawObjectOnTheScreen(bird.Site(), bird.Symbole());

		// 墙移动移动一格的时间间隔
		TimeControl wallMoveTime({ 150 });
		// 鸟上升移动一格的时间间隔
		TimeControl birdUp({ 50, 90, 140 });
		// 鸟下落移动一格的时间间隔
		TimeControl birdDown({ 150,110,90,70,60 });

		Sleep(1000);

		// 主场景循环
		for (birdUp.SetEnd(), birdDown.Reset(), wallMoveTime.Reset() // 鸟初始为下落状态
			;;)
		{
			if (birdDown.TimeTargetComplete()) // 判断鸟是否需要下落
			{
				bird.MovedParallel(MOVEDIR::FALL);

				if (obs.CollisionWithTheWalls(bird)) // 判断移动后是否相撞
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

				// 如果已到达最后一个时间间隔，继续使用这个时间间隔
				if (birdDown.ControlEnd())
				{
					birdDown.ResetToLastInterval();
				}
			}
			else if (birdUp.TimeTargetComplete()) // 判断鸟是否需要上升
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

				// 如果上升到顶点，开始下落
				if (birdUp.ControlEnd())
				{
					birdDown.Reset();
				}
			}

			// 键盘有输入时，开始上升
			if (GetAsyncKeyState(38) && 0x8000)
			{
				birdDown.SetEnd();
				birdUp.Reset();
			}

			// 判断墙是都需要移动
			if (wallMoveTime.TimeTargetComplete())
			{
				obs.MovingAllWall(MOVEDIR::BACKWARD, 1);

				if (obs.CollisionWithTheWalls(bird, score))
				{
					// 强调鸟的位置
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