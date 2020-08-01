#include "Knife.h"
#include "Whip.h"
#include "GameObject.h"
#include "Simon.h"
#include "Flame.h"
#include "Knife.h"
#include "SmallCandle.h"
#include "Simon.h"
#include "Candle.h"
#include "Knight.h"
#include "SmallCandle.h"
#include "SecretBrick.h"
#include "Bat.h"
#include "Zombie.h"
#include "Flea.h"
#include "Monkey.h"
#include "Skeleton.h"
#include "Raven.h"
#include"HitEffects.h"

CKnife * CKnife::__instance = NULL;

void CKnife::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (visible)
	{
		CGameObject::Update(dt);
		vx = (nx > 0) ? KNIFE_FLYING_SPEED : -KNIFE_FLYING_SPEED;

		if(!IsInViewport())
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
				if (dynamic_cast<CSmallCandle *>(e->obj)
					|| dynamic_cast<CCandle *>(e->obj)
					|| dynamic_cast<CKnight *>(e->obj)
					|| dynamic_cast<CBat *>(e->obj)
					|| dynamic_cast<CFlea *>(e->obj)
					|| dynamic_cast<CMonkey *>(e->obj)
					|| dynamic_cast<CZombie *>(e->obj)
					|| dynamic_cast<CSkeleton *>(e->obj)
					|| dynamic_cast<CRaven *>(e->obj)
					|| dynamic_cast<CRaven *>(e->obj))
				{
					if (e->nx != 0 || e->ny != 0)
					{
						vx = 0;
						e->obj->BeHit(this->damage);
						this->SetVisible(false);
						CHitEffects::GetInstance()->Show(e->obj->x, e->obj->y);

					}
				}

			}
		}
			
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void CKnife::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + KNIFE_BBOX_WIDTH;
	bottom = top + KNIFE_BBOX_HEIGHT;
}

void CKnife::ChoiceAnimation()
{
	currentAniID = (nx > 0) ?
		(int)KnifeAniID::knifeRight :
		(int)KnifeAniID::knifeLeft;
}

void CKnife::Render()
{
	ChoiceAnimation();
	CGameObject::Render();
}

CKnife * CKnife::GetInstance()
{
	if (__instance == NULL)__instance = new CKnife();

	return __instance;
}

CKnife::CKnife()
{
	visible = false;
	damage = 1;
}