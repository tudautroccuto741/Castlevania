#include "Flame.h"

void CFlame::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + FLAME_BBOX_WIDTH;
	bottom = top + FLAME_BBOX_HEIGHT;
}

void CFlame::StartToBurn()
{
	startBurnTime = GetTickCount();
}

void CFlame::Render()
{
	if (GetVisible())
	{
		if (GetTickCount() - startBurnTime > BURNING_TIME)
		{
			this->SetVisible(false);
			ResetAnimationTimer(currentAniID);
		}
		else			
			CGameObject::Render();
	}
}

CFlame::CFlame()
{
	this->currentAniID = (int)FlameAniID::idleFlame;
	visible = true;
}