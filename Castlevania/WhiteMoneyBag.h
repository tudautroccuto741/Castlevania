#pragma once
#include "GameObject.h"
#include "Animations.h"
#define WHITEMONEYBAG_BBOX_WIDTH	30
#define WHITEMONEYBAG_BBOX_HEIGHT	30
enum class WhiteMoneyBagAniID
{
	idle = 100001
};
class CWhiteMoneyBag : public CGameObject
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL)override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	CWhiteMoneyBag();
};