#include "Boomerang.h"
#include "Whip.h"
#include "GameObject.h"
#include "Simon.h"
#include "SmallCandle.h"
#include "Flame.h"
#include "BoomerangItem.h"
#include "Brick.h"
#include "Bat.h"
#include "Knight.h"
#include "Game.h"

CBoomerang * CBoomerang::__instance = NULL;

void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (visible)
	{
		CGameObject::Update(dt);
		vx = (nx > 0) ? BOOMERANG_FLYING_SPEED : -BOOMERANG_FLYING_SPEED;
		CGame *game = CGame::GetInstance();
		// The viewport bounding box
		float vpLeft, vpTop, vpRight, vpBottom;
		game->CamereBoundingBox(vpLeft, vpTop, vpRight, vpBottom);

		// The object bounding box
		float left, top, right, bottom;
		this->GetBoundingBox(left, top, right, bottom);

		if (isReturn == 0)
		{
			start_time_turn_around = GetTickCount();
		}
		else if (isReturn >= 2)
		{
			isReturn = 0;
			this->SetVisible(false);
			start_time_turn_around = 0;
		}

		//probelm is here??????????????????????????????????????????????????
		if (start_time_turn_around > 0)
		{
			if ((left <= vpLeft && vx < 0)
				|| (right >= vpRight && vx > 0) 
				|| (GetTickCount() - start_time_turn_around >= BOOMERANG_FLYING_TIME && isReturn < 1))
			{
				DebugOut(L"[INFO] Touch CameraBoundingBox\n");
				isReturn++;
				SetDirection(-nx);
			}
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
					||dynamic_cast<CBat*>(e->obj)
					|| dynamic_cast<CKnight *>(e->obj))
				{
					if (e->nx != 0 || e->ny != 0)
					{
						vx = 0;
						e->obj->BeHit(damage);
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
	if (isReturn >= 1 && nx > 0)
	{
		currentAniID = (int)BoomerangAniID::BoomerangRight;
	}
	else if (isReturn >= 1 && nx < 0)
	{
		currentAniID = (int)BoomerangAniID::BoomerangLeft;
	}
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
	start_time_turn_around = 0;
	visible = false;
	damage = 2;
	isReturn = 0;
}