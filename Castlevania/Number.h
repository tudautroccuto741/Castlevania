#pragma once
#include "GameObject.h"

#define NUMBER_BBOX_WIDTH			22
#define NUMBER_BBOX_HEIGHT			10	


enum class NumberAniID
{
	IDLE1 = 2222222,
	IDLE2 = 3333333
};

class CNumber : public CGameObject
{
	DWORD start_visible = 0;
public:

	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT> * coObjects = NULL) override;
	CNumber();
};