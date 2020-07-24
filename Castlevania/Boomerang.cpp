#include "Boomerang.h"
#include "Whip.h"
#include "GameObject.h"
#include "Simon.h"
#include "SmallCandle.h"
#include "Flame.h"
#include "BoomerangItem.h"
#include "Brick.h"
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
#include "Game.h"

CBoomerang * CBoomerang::__instance = NULL;

void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	CGame *game = CGame::GetInstance();
	// The viewport bounding box
	float vpLeft, vpTop, vpRight, vpBottom;
	game->CamereBoundingBox(vpLeft, vpTop, vpRight, vpBottom);

	// The object bounding box
	float left, top, right, bottom;
	this->GetBoundingBox(left, top, right, bottom);


	if (isReturn > 1)
	{
		isReturn = 0;
		vx = 0;
		this->SetVisible(false);
	}

	if (vx == 0 && visible)
	{
		CSimon::GetInstance()->GetPosition(xS, yS);
	}

	if ((left <= vpLeft && vx < 0)
		|| (right >= vpRight && vx > 0)
		|| x >= xS + SIMON_IDLE_BBOX_WIDTH + BOOMERANG_DISTANCE_WITH_SIMOM && nx > 0
		|| x + BOOMERANG_BBOX_WIDTH + BOOMERANG_DISTANCE_WITH_SIMOM <= xS && nx < 0)
	{
		DebugOut(L"[INFO] Touch CameraBoundingBox\n");
		isReturn = isReturn + 1;
		SetDirection(-nx);
	}
	vx = nx * BOOMERANG_FLYING_SPEED;


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
				|| dynamic_cast<CSecretBrick *>(e->obj)
				|| dynamic_cast<CBat *>(e->obj)
				|| dynamic_cast<CFlea *>(e->obj)
				|| dynamic_cast<CMonkey *>(e->obj)
				|| dynamic_cast<CZombie *>(e->obj)
				|| dynamic_cast<CSkeleton *>(e->obj)
				|| dynamic_cast<CRaven *>(e->obj))
			{
				if (e->nx != 0 || e->ny != 0)
				{
					vx = 0;
					e->obj->BeHit(damage);
				}
			}
			if (dynamic_cast<CSimon *>(e->obj))
			{
				if (e->nx != 0)
				{
					isReturn = 0;
					vx = 0;
					SetVisible(false);
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
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

void CBoomerang::SetVisible(bool visible)
{
	CGameObject::SetVisible(visible);
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
	vx = 0;
	visible = false;
	damage = 2;
	isReturn = 0;
}