#pragma once
#include "GameObject.h"
#include "Animations.h"
#define BOOMERANG_ITEM_BBOX_WIDTH 30
#define BOOMERANG_ITEM_BBOX_HEIGHT 28

enum class BoomerangItemAniID
{
	Boomerang = 900
};

class CBoomerangItem : public CGameObject
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	CBoomerangItem();
};