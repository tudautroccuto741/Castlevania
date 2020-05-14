#include "SmallCandle.h"

void CSmallCandle::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + SMALL_CANDLE_BBOX_WIDTH;
	b = y + SMALL_CANDLE_BBOX_HEIGHT;
}

CSmallCandle::CSmallCandle()
{
	this->currentAniID = (int)SmallCandleAniID::idleSmallCandle;
	this->visible = true;
}
