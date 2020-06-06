#pragma once
#include "GameObject.h"

#define ROCK_BBOX_WIDTH			14
#define ROCK_BBOX_HEIGHT		16	
#define ROCK_FALL_GRAVITY		0.001f

enum class RockAniID
{
	IDLE = 4012,
};

/*
	The object will be dropped out when we break something
*/
class CRock : public CGameObject
{
public:

	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT> * coObjects = NULL) override;
	CRock();
};

