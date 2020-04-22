#pragma once
#include "GameObject.h"
#include "Animations.h"
#define KNIFE_BBOX_WIDTH 32
#define KNIFE_BBOX_HEIGHT 18

enum class KnifeAniID
{
	idleKnife = 801
};
class CKnife : public CGameObject
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	CKnife();
};

