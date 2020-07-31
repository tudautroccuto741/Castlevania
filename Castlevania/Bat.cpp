#include "Bat.h"
#include "Simon.h"
void CBat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = BAT_BBOX_WIDTH + left;
	bottom = BAT_BBOX_HEIGHT + top;
}

void CBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (CSimon::GetInstance()->GetFreezing())
		return;
	CGameObject::Update(dt);
	// Update the position
	x += dx;
	y += dy;
	/*vx = nx * BAT_SPEED_VX;*/
	float xB, yB;
	CSimon::GetInstance()->GetPosition(xB, yB);
	if (xB <= DISTANCE_WITH_SIMON_X+x && yB <= DISTANCE_WITH_SIMON_Y+y)
	{
		SetState((int)BatStateID::stateflyingRight);
	}
	if (vx == 0)
	{
		SetState((int)BatStateID::stateidle);
	}
	if (y >= start_y + DISTANCE_BAT_FLYING_HORIZONTAL)
	{
		this->y = start_y + DISTANCE_BAT_FLYING_HORIZONTAL;
		vx = BAT_SPEED_VX;
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
		SetVisible(false);
}

void CBat::SetState(int state)
{
	switch (state)
	{
	case (int)BatStateID::stateidle:
		vx = 0;
		GetPosition(x, start_y);
		break;
	case (int)BatStateID::stateflyingRight:
		vx = BAT_SPEED_VX;
		vy = BAT_SPEED_VY;
		break;
	default:
		break;
	}
}

void CBat::ChoiceAnimations()
{
	if (vx != 0)
	{
		currentAniID = (int)BatAniID::flyingRight;
	}
	else
	{
		currentAniID = (int)BatAniID::idle;
	}
}

void CBat::Render()
{
	if (CSimon::GetInstance()->freezing)
	{
		animations->GetInstance()->Get(currentAniID)->RenderbyFrame(animations->Get(currentAniID)->GetCurrentFrame(), x, y, alpha);
	}
	else
	{
		ChoiceAnimations();
		CGameObject::Render();
	}
}

//void CBat::Destroy()
//{
//
//}

CBat::CBat()
{
	vx = 0;
	vy = 0;

	health =BAT_DEFAULT_HEALTH;
	damage = BAT_DAMAGE;
	visible = true;
}