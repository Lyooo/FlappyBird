#pragma once

#include <iostream>
#include <Windows.h>
#include "object.h"

// �ƶ���굽siteλ��
void GotoXY(const COORD& site);

// ����Ļ�ϴ�ӡһ�з���s
void DrawHorizontal(const COORD& begin, SHORT endX, char s);

// ����Ļ�ϴ�ӡһ������s
void DrawVertical(const COORD& begin, SHORT endY, char s);