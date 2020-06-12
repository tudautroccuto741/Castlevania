#pragma once
#include "GameObject.h"
#include "Animations.h"
#define BALL_BBOX_WIDTH		28
#define BALL_BBOX_HEIGHT	32
enum class BallAniID
{
	idle = 100005
};
class CBall : public CGameObject
{
public:

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL)override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	CBall();
};

