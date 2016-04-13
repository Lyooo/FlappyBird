#pragma once

#include <iostream>
#include <Windows.h>
#include "object.h"

// 移动光标到site位置
void GotoXY(const COORD& site);

// 在屏幕上打印一行符号s
void DrawHorizontal(const COORD& begin, SHORT endX, char s);

// 在屏幕上打印一竖符号s
void DrawVertical(const COORD& begin, SHORT endY, char s);