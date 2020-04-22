#pragma once
#include"GameObject.h"
#define WHIP_ITEM_BBOX_WIDTH 32
#define WHIP_ITEM_BBOX_HEIGHT 32

enum class WhipItemAniID
{
	idleWhipItem = 701
};
class CWhipItem : public CGameObject
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	CWhipItem();
};

