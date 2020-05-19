#include "Boomerang.h"
#include "Whip.h"
#include "GameObject.h"
#include "Simon.h"
#include "SmallCandle.h"
#include "Flame.h"
#include "BoomerangItem.h"
#include "Brick.h"

CBoomerang * CBoomerang::__instance = NULL;

void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (visible)
	{
		nx = CSimon::GetInstance()->GetDirection();
		CGameObject::Update(dt);
		vx = (nx > 0) ? BOOMERANG_FLYING_SPEED : -BOOMERANG_FLYING_SPEED;
		if (x < 0 || x>448)
		{
			this->vx = (-this->nx)*BOOMERANG_FLYING_SPEED;
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

void CBoomerang::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + BOOMERANG_BBOX_WIDTH;
	bottom = top + BOOMERANG_BBOX_HEIGHT;
}

void CBoomerang::ChoiceAnimation()
{
	int nxKn;
	nxKn = CSimon::GetInstance()->GetDirection();
	currentAniID = (nxKn > 0) ?
		(int)BoomerangAniID::BoomerangRight :
		(int)BoomerangAniID::BoomerangLeft;
}

void CBoomerang::Render()
{
	ChoiceAnimation();
	CGameObject::Render();
}

CBoomerang * CBoomerang::GetInstance()
{
	if (__instance == NULL)__instance = new CBoomerang();

	return __instance;
}

CBoomerang::CBoomerang()
{
	visible = false;
}