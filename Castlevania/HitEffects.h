#pragma once
#pragma once
#include "HitEffect.h"
class CHitEffects
{
	static CHitEffects * __instance;
	vector<CHitEffect *> effects;

public:

	void Add(CHitEffect * effect);
	void Show(float x, float y);
	void Clear();
	static CHitEffects * GetInstance();
};
