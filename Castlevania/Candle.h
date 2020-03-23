#pragma once
#include "GameObject.h"
#include "Animations.h"

enum class CandleAniID {
	STAND = 600, 
	ID_TEX_CANDLE = 200
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
