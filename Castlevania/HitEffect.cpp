#include "HitEffect.h"

void CHitEffect::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + HITEFFECT_BBOX_WIDTH;
	bottom = y + HITEFFECT_BBOX_HEIGHT;
}

void CHitEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (visible)
	{
		if (start_visible < 300)
		{
			start_visible += dt;
		}
		else
		{
			SetVisible(false);
			start_visible = 0;
		}
	}

	// Update position
	x += dx;
	y += dy;

	// Re-set the state
	if (this->IsInViewport() == false)
		this->SetVisible(false);
}

CHitEffect::CHitEffect()
{
	currentAniID = (int)HitEffectAniID::IDLE;
}