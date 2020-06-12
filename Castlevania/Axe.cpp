#include "Axe.h"
#include "Simon.h"
#include "SmallCandle.h"

CAxe * CAxe::__instance = NULL;

void CAxe::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + AXE_BBOX_WIDTH;
	bottom = y + AXE_BBOX_HEIGHT;
}

void CAxe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	// Falling down
	vy += AXE_GRAVITY * this->dt;


	// Choose animation 
	ChoiceAnimations();

	if (!IsInViewport())
	{
		this->SetVisible(false);
	}
	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	vector<LPCOLLISIONEVENT> coEventsResult;

	float min_tx, min_ty, nx = 0, ny;

	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
	}
	else
	{
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		x += min_tx * dx;
		y += min_ty * dy;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			// collision with candle
			if (dynamic_cast<CSmallCandle *>(e->obj))
			{
				e->obj->BeHit(this->damage);
			}
		}
	}

	// Clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	
}

void CAxe::ChoiceAnimations()
{
	currentAniID = (nx > 0) ?
		(int)AxeAniID::FlyRight
		: (int)AxeAniID::FlyLeft;
}

void CAxe::SetVisible(bool visible)
{
	CGameObject::SetVisible(visible);

	if (visible)
	{
		vx = (nx > 0) ? AXE_FLY_SPEED_VX : -AXE_FLY_SPEED_VX;
		vy = AXE_FLY_SPEED_VY;
	}
}

CAxe * CAxe::GetInstance()
{
	if (__instance == NULL)__instance = new CAxe();

	return __instance;
}

CAxe::CAxe()
{
	visible = false;
	this->damage = AXE_DAMAGE;
}