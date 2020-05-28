#pragma once
#include "GameObject.h"
#include "Animations.h"

#define SMALL_HEART_BBOX_WIDTH	16
#define SMALL_HEART_BBOX_HEIGHT 16

enum class SmallHeartAniID
{
	idleSmallHeart = 602
};

class CSmallHeart : public CGameObject
{
	float vxSH;
public:
	void SetVisible(bool visible)override;
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL)override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	CSmallHeart();
};