#pragma once
#include "GameObject.h"
#include "Animations.h"
#define CANDLE_BBOX_WIDTH 32
#define CANDLE_BBOX_HEIGHT 64

enum class CandleAniID
{
	idleCandle = 401
};

class CCandle : public CGameObject
{
public:

	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	CCandle();
};