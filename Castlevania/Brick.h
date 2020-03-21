#pragma once
#include "GameObject.h"

class CBrick : public CGameObject
{
	float x;
	float y;

	float vx;

	vector<LPANIMATION> animations;
public:

	void Update(DWORD dt);
	void Render();
};
