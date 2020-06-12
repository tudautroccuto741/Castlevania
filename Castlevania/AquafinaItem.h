#pragma once
#include "GameObject.h"
#include "Animations.h"
#define AQUAFINAITEM_BBOX_WIDTH		32
#define AQUAFINAITEM_BBOX_HEIGHT	32

enum class AquafinaItemAniID
{
	idle = 100006
};

class CAquafinaItem : public CGameObject
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL)override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	CAquafinaItem();
};

