/***********************************/
/*     所有在屏幕上打印的函数       */
/**********************************/

#pragma once

#ifndef _DRAW_
#define _DRAW_

#include <iostream>
#include "object.h"

namespace Draw
{
	void GotoXY(const COORD& site);

	void DrawCowOnTheScreen(const Object::RangeType& xRange, SHORT y, char s);

	void DrawColumnOnTheScreen(const Object::RangeType & yRange, SHORT x, char s);

	void DrawObjectOnTheScreen(
		const Object::ObjectSite& o, char s,
		const Object::RangeType& xOutOfRange = { -1,MAXSHORT });
}

#endif // !_DRAW_