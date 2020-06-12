#include "Meat.h"
#include "Brick.h"

void CMeat::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + MEAT_BBOX_WIDTH;
	b = y + MEAT_BBOX_HEIGHT;
}

void CMeat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy = GAME_GRAVITY * dt;				// simple fall down

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);


	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx;
		y += min_ty * dy;

		for (UINT i = 0; i < coEventsResult.size(); ++i)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBrick *>(e->obj))
			{
				// Block brick
				if (e->ny < 0)
				{
					y += 0.4f * e->ny;
					vy = 0;
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (!this->IsInViewport())
		SetVisible(false);
}

CMeat::CMeat()
{
	this->currentAniID = (int)MeatAniID::idle;
	visible = false;
}