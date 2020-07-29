#pragma once
#include "GameObject.h"

#define CROWN_BBOX_WIDTH		32
#define CROWN_BBOX_HEIGHT		32
#define CROWN_GROWING_UP_SPEED	0.05
#define LIMITED_GROW_UP_Y		704
#define DISTANCE_SIMON_GROW_UP_X 894
#define DISTANCE_SIMON_GROW_UP_Y 574

enum class CrownAniID
{
	IDLE = 40131,
	GROWUP = 4013
};

class CCrown : public CGameObject
{
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT> * coObjects = NULL) override;
	CCrown();
};

