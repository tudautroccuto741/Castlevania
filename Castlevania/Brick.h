#pragma once
#include "GameObject.h"
#include "Animations.h"
#define BRICK_BBOX_WIDTH  32
#define BRICK_BBOX_HEIGHT 32

class CBrick : public CGameObject
{
	
public:
	virtual void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	CBrick();
};