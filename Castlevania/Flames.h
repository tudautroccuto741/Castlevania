#pragma once
#include "Flame.h"
#include "GameObject.h"

/*
	The class helps managing the Flame:
*/
class CFlames
{
	vector<CFlame *> flames;

	static CFlames * __instance;


public:

	void Add(CFlame * flame);
	void ShowFlame(LPGAMEOBJECT obj);
	void Clear();
	CFlames() { ; }
	static CFlames * GetInstance();
};

