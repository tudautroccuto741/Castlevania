#pragma once
#include "GameObject.h"

#define HITEFFECT_BBOX_WIDTH			16
#define HITEFFECT_BBOX_HEIGHT			20	

enum class HitEffectAniID
{
	IDLE = 4444444
};

class CHitEffect : public CGameObject
{
	DWORD start_visible = 0;
public:

	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT> * coObjects = NULL) override;
	CHitEffect();
};
