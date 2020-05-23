#pragma once
#include "GameObject.h"
#include "Animations.h"

#define SECRET_BRICK_BBOX_WIDTH  32
#define SECRET_BRICK_BBOX_HEIGHT 32

enum class SecretBrickAniID
{
	idle = 401
};

class CSecretBrick : public CGameObject
{
public:
	virtual void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	CSecretBrick();
};

