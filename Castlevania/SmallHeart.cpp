#include "SmallHeart.h"
#include "Brick.h"

void CSmallHeart::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + SMALL_HEART_BBOX_WIDTH;
	b = y + SMALL_HEART_BBOX_HEIGHT;
}

void CSmallHeart::SetVisible(bool visible)
{
	CGameObject::SetVisible(visible);
	if (this->GetVisible())
	{
		vy = SMALL_HEART_FALL_SPEED_Y;
		vx = SMALL_HEART_MAX_SPEED_X;
	}
}

void CSmallHeart::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	vy = 0.04;				// simple fall down

	// Horizontal movement
	vx += vxSH * dt;
	if (abs(vx) > SMALL_HEART_MAX_SPEED_X && vx * vxSH > 0) vxSH = -vxSH;

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
				vy = vx = 0;
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (!this->IsInViewport())
		SetVisible(false);
}

CSmallHeart::CSmallHeart()
{
	this->vxSH = SMALL_HEART_SPEED_VX;
	vy = SMALL_HEART_FALL_SPEED_Y;
	vx = SMALL_HEART_MAX_SPEED_X;
	this->currentAniID = (int)SmallHeartAniID::idleSmallHeart;
	visible = false;
}