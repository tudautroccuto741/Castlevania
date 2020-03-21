#pragma once
#include "GameObject.h"
#include "Animations.h"

class CSimon : public CGameObject
{
	float x = 0;
	float y = 0;

	float vx = 0.07f;

	int currentState;

	vector<LPANIMATION> animations;
public:

	void Update(DWORD dt);
	void Render();
};
