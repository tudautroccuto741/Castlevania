#pragma once
#include "GameObject.h"
#include "Animations.h"
#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16
enum class BrickAniID 
{
	IDTexBrick = 300,
	idleBrick = 301
};

class CBrick : public CGameObject
{
public:

	void Update(DWORD dt);
	virtual void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	CBrick();
};
