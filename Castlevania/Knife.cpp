#include "Knife.h"
#include "Whip.h"
#include "GameObject.h"
#include "Simon.h"
#include "Candle.h"
#include "Flame.h"
#include "Knife.h"

CKnife * CKnife::__instance = NULL;

void CKnife::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (visible)
	{
		nx = CSimon::GetInstance()->GetDirection();
		CGameObject::Update(dt);
		vx = (nx > 0) ? KNIFE_FLYING_SPEED : -KNIFE_FLYING_SPEED;
		if (x < 0 || x>1504)
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
				if (dynamic_cast<CCandle *>(e->obj))
				{
					if (e->nx != 0 || e->ny != 0)
					{
						vx = 0;
						e->obj->Destroy();
						this->SetVisible(false);
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
	int nxKn;
	nxKn = CSimon::GetInstance()->GetDirection();
	currentAniID = (nxKn > 0) ?
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
}