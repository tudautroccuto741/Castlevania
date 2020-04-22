#pragma once
#include "GameObject.h"
#include "Animations.h"
#define HEART_BBOX_WIDTH 24
#define HEART_BBOX_HEIGHT 20

enum class HeartAniID
{
	idleHeart = 601
};
class CHeart : public CGameObject
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL)override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	CHeart();
};

