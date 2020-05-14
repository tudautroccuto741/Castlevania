#pragma once
#include "GameObject.h"
#include "Animations.h"
#define SMALL_CANDLE_BBOX_WIDTH 16
#define SMALL_CANDLE_BBOX_HEIGHT 32

enum class SmallCandleAniID
{
	idleSmallCandle = 402
};

class CSmallCandle : public CGameObject
{
public:

	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	CSmallCandle();
};