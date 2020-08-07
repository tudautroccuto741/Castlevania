#pragma once
#include "GameObject.h"
#include "Animations.h"
#define MEAT_BBOX_WIDTH		32
#define MEAT_BBOX_HEIGHT	26

enum class MeatAniID
{
	idle = 100004
};

class CMeat : public CGameObject
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL)override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	CMeat();
};
