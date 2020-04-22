#include "Flames.h"

#include "debug.h"

CFlames * CFlames::__instance = NULL;

void CFlames::Add(CFlame * flame)
{
	flame->SetVisible(false);
	flames.push_back(flame);
}

/*
	Show a flame at the center position of the destroyed object given.
*/
void CFlames::ShowFlame(LPGAMEOBJECT obj)
{
	// Show at the central position of the object
	float l, t, r, b;
	obj->GetBoundingBox(l, t, r, b);
	float xCentral = (l + r) / 2;
	float yCentral = (t + b) / 2;

	CFlame* flame;

	for (UINT i = 0; i < flames.size(); ++i)
	{
		flame = flames[i];
		if (flame->GetVisible()==false)
		{
			flame->SetVisible(true);
			flame->StartToBurn();

			flame->SetHoldingItem(obj->GetHoldingItem());
			// Calibrate the flame position to appear at the central of the objects
			flame->SetPosition(
				xCentral - FLAME_BBOX_WIDTH / 2,
				yCentral - FLAME_BBOX_HEIGHT / 2);

			break;
		}
	}
}

CFlames * CFlames::GetInstance()
{
	if (__instance == NULL)
		__instance = new CFlames();

	return __instance;
}
