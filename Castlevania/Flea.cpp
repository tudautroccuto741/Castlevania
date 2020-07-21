#include "Flea.h"
#include "Simon.h"

void CFlea::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = FLEA_BBOX_WIDTH + left;
	bottom = FLEA_BBOX_HEIGHT + top;
}

void CFlea::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	// Update the position
	x += dx;
	y += dy;

	FindSimon();

	if (vy == 0)
	{
		SetState((int)FleaStateID::stateFlying);
	}
	
	if (CSimon::GetInstance()->GetUntouchable() == 1)
	{
		SetState((int)FleaStateID::stateTouchingSimon);	
	}
	// flea flying
	if (y + 32 <= start_y)
	{
		vy = FLEA_SPEED_VY;
		isUp = true;
	}
	if (y >= start_y && isUp) {
		vy = 0;
		isUp = false;
	}

	// untouchable
	if (start_untouchable != 0)
	{
		Untouchable();
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);
	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		x += min_tx * dx;
		y += min_ty * dy;

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (this->IsInViewport() == false)
		health = 0;
}

void CFlea::FindSimon()
{
	float xS, yS;
	CSimon::GetInstance()->GetPosition(xS, yS);

	if (xS > x + FLEA_BBOX_WIDTH)
	{
		this->nx = 1;
	}
	else if (xS + SIMON_IDLE_BBOX_WIDTH < x)
	{
		this->nx = -1;
	}
}

void CFlea::SetState(int state)
{
	switch (state)
	{
	case (int)FleaStateID::stateFlying:
		vx = nx*FLEA_SPEED_VX;
		GetPosition(x, start_y);
		break;
	case (int)FleaStateID::stateTouchingSimon:
		vx = nx*FLEA_SPEED_VX;
		vy = -FLEA_SPEED_VY;
		break;
	default:
		break;
	}
}

void CFlea::ChoiceAnimations()
{
	if (vx > 0)
	{
		currentAniID = (int)FleaAniID::flyingRight;
	}
	else
	{
		currentAniID = (int)FleaAniID::flyingLeft;
	}
}

void CFlea::Render()
{
	ChoiceAnimations();
	CGameObject::Render();
}

CFlea::CFlea()
{
	vx = -FLEA_SPEED_VX;
	vy = 0;
	health = FLEA_DEFAULT_HEALTH;
	damage = FLEA_DAMAGE;
	visible = false;
	isUp = false;
}