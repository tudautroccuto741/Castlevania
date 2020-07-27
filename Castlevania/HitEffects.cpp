#include "HitEffects.h"

CHitEffects * CHitEffects::__instance = NULL;

void CHitEffects::Add(CHitEffect * effect)
{
	effect->SetVisible(false);
	effects.push_back(effect);
}

void CHitEffects::Show(float x, float y)
{
	CHitEffect * effect = NULL;

	for (UINT i = 0; i < effects.size(); i++)
	{
		if (effects[i]->GetVisible() == false)
		{
			effect = effects[i];
			i++;
			break;
		}
	}
	if (effect != NULL)
	{
		effect->SetPosition(x, y);
		effect->SetVisible(true);
	}

}

void CHitEffects::Clear()
{
	effects.clear();
}

CHitEffects * CHitEffects::GetInstance()
{
	if (__instance == NULL)
		__instance = new CHitEffects();

	return __instance;
}
