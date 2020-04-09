#pragma once
#include "Flame.h"
#include "GameObject.h"
/*
	Manager flame
*/
class CFlames
{
	vector<LPFLAME> flames;
	static CFlames * __instance;
	CFlames() = default;

public:
	void Add(CFlame*flame);
	void ShowFlame(LPGAMEOBJECT obj);

	static CFlames * GetInstance();

};

