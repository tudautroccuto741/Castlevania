#pragma once
#include "GameObject.h"
#include "Animations.h"

using namespace std;

class CWeapons:CGameObject
{
protected:
	float x;
	float y;

	int nx;

	//static class CWeapons * __instance;
public:
	
	virtual void Update(DWORD dt);
	virtual void Render();
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	//static CWeapons * GetInstance();
};


