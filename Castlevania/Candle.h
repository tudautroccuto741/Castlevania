#pragma once
#include "GameObject.h"
#include "Animations.h"

enum class CandleAniID 
{
	IDTexCandle = 200,
	idleCandle = 201
};

class CCandle : public CGameObject
{
	float x = 0;
	float y = 0;

	vector<LPANIMATION> animations;
public:

	void Update(DWORD dt);
	void Render();
};
