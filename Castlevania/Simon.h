#pragma once
#include "GameObject.h"
#include "Animations.h"

enum class SimonAniId {
	IDLEGORIGHT = 500,
	IDLEGOLEFT = 501
};

class CSimon : public CGameObject
{
	float x = 0;
	float y = 0;

	float vx = 0.07f;

	vector<LPANIMATION> animations;
public:

	void Update(DWORD dt);
	void Render();
};
