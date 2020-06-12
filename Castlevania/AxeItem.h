#pragma once
#include "GameObject.h"
#include "Animations.h"
#define AXEITEM_BBOX_WIDTH		30
#define AXEITEM_BBOX_HEIGHT		28

enum class AxeItemAniID
{
	idle = 100007
};

class CAxeItem : public CGameObject
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL)override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	CAxeItem();
};

