#pragma once
#include "GameObject.h"
#include "Animations.h"

#define SECRET_BRICK_BBOX_WIDTH  32
#define SECRET_BRICK_BBOX_HEIGHT 32

#define CANNOT_BE_HIT_TIME		 200

enum class SecretBrickAniID
{
	idle = 4011
};

class CSecretBrick : public CGameObject
{
	static DWORD cannot_be_hit_start;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void Destroy() override;
	void BeHit(int damage) override;
	CSecretBrick();
};

