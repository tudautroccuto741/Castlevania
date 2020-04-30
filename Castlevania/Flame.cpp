#include "Flame.h"
#include "Items.h"

void CFlame::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + FLAME_BBOX_WIDTH;
	bottom = top + FLAME_BBOX_HEIGHT;
}

void CFlame::Render()
{
	if (GetVisible()==true)
	{
		if (GetTickCount() - burnStartTime > BURNING_TIME)
		{
			this->Destroy();
		}
		else
			CGameObject::Render();
	}
}

void CFlame::Destroy()
{
	CItems::GetInstance()->CheckAndDrop(this);
	SetVisible(false);
}

void CFlame::StartToBurn()
{
	burnStartTime = GetTickCount();
}

CFlame::CFlame()
{
	currentAniID = (int)FlameAniID::idleFlame;
}


