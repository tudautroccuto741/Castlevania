#pragma once
#include "GameObject.h"
#include "Animations.h"
#define REDMONEYBAG_BBOX_WIDTH	30
#define REDMONEYBAG_BBOX_HEIGHT	30
enum class RedMoneyBagAniID
{
	idle = 100002
};
class CRedMoneyBag : public CGameObject
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL)override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	CRedMoneyBag();
};