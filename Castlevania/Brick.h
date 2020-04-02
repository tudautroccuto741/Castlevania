#pragma once
#include "GameObject.h"
#include "Animations.h"
#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16
enum class BrickAniID 
{
	IDTexBrick = 300,
	idlebrick = 301
};

class CBrick : public CGameObject
{
	float x = 0;
	float y = 0;

public:

	void Update(DWORD dt);
	void Render();
	//virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};
