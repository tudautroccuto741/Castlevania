#pragma once
#include "GameObject.h"
#include "Animations.h"

enum class BrickAniID {
	STAND = 600,
	ID_TEX_BRICK = 100
};

class CBrick : public CGameObject
{
	float x = 0;
	float y = 0;

	vector<LPANIMATION> animations;
public:

	void Update(DWORD dt);
	void Render();
};
