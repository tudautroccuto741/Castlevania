#include "Candle.h"

void CCandle::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + CANDLE_BBOX_WIDTH;
	b = y + CANDLE_BBOX_HEIGHT;
}
CCandle::CCandle()
{
	this->currentAniID = (int)CandleAniID::idleCandle;
	visible = true;
}