#include "Aquafina.h"
#include "SmallCandle.h"
#include "Brick.h"

CAquafina * CAquafina::__instance = NULL;

void CAquafina::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;

	if (currentAniID == (int)AquafinaAniID::boom)
	{
		right = left + AQUAFINA_BOOM_BBOX_WIDTH;
		bottom = top + AQUAFINA_BOOM_BBOX_HEIGHT;
	}
	else
	{
		right = left + AQUAFINA_IDLE_BBOX_WIDTH;
		bottom = top + AQUAFINA_IDLE_BBOX_HEIGHT;
	}
}

void CAquafina::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	// Falling down
	if (boom == false)
		vy += AQUAFINA_IDLE_GRAVITY * this->dt;


	// Choice animation 
	ChoiceAnimations();


	// boooooooooom
	if (boom_start != 0)
		if (GetTickCount() - boom_start > AQUAFINA_BOOM_TIME)
		{
			boom_start = 0;
			this->SetVisible(false);
		}


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
			else if (dynamic_cast<CBrick*>(e->obj))
			{
				vx = vy = 0;
				if (!boom)
				{
					x += (AQUAFINA_IDLE_BBOX_WIDTH - AQUAFINA_BOOM_BBOX_WIDTH) / 2;
					y += (AQUAFINA_IDLE_BBOX_HEIGHT - AQUAFINA_BOOM_BBOX_HEIGHT);

					boom = true;
					boom_start = GetTickCount();
				}
			}
		}
	}


	// Clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CAquafina::SetVisible(bool visible)
{
	CGameObject::SetVisible(visible);
	if (visible)
	{
		vx = (nx > 0) ?
			AQUAFINA_IDLE_FLY_SPEED_VX :
			-AQUAFINA_IDLE_FLY_SPEED_VX;

		vy = AQUAFINA_IDLE_FLY_SPEED_VY;

		boom = false;
	}
}

void CAquafina::ChoiceAnimations()
{
	if (boom)
	{
		currentAniID = (int)AquafinaAniID::boom;
	}
	else
	{
		currentAniID = (nx > 0) ?
			(int)AquafinaAniID::right
			: (int)AquafinaAniID::left;
	}
}

CAquafina * CAquafina::GetInstance()
{
	if (__instance == NULL)__instance = new CAquafina();

	return __instance;
}

CAquafina::CAquafina()
{
	visible = false;
	this->damage = AQUAFINA_DAMAGE;
}