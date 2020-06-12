#pragma once
#include "GameObject.h"
#include "Animations.h"
#define IIiTEM_BBOX_WIDTH	28
#define IIiTEM_BBOX_HEIGHT	28
enum class IIitemAniID
{
	idle = 100003
};
class CIIitem : public CGameObject
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL)override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	CIIitem();
};

