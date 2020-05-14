#include "Knight.h"
#include "Brick.h"

//CKnight * CKnight::__instance = NULL;
void CKnight::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	x += dx;
	vy += KNIGHT_GRAVITY * dt;
	vx = (nx > 0) ? KNIGHT_WALKING_SPEED : -KNIGHT_WALKING_SPEED;
	if (x > 288)
	{
		SetDirection(-1);
	}
	if (x < 72)
	{
		SetDirection(1);
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


		// collision logic with other objects
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			// collision with brick

			if (dynamic_cast<CBrick *>(e->obj))
			{
				if (e->ny != 0)
				{
					y += ny * 0.4f;
					vy = 0;
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CKnight::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + KNIGHT_IDLE_BBOX_WIDTH;
	bottom = y + KNIGHT_IDLE_BBOX_HEIGHT;
}

void CKnight::ChoiceAnimation()
{
	int nxk = GetDirection();
	if (vx != 0)
	{
		currentAniID = (nxk > 0) ?
			(int)KnightAniId::walkRight :
			(int)KnightAniId::walkLeft;
	}
}

void CKnight::Render()
{
	ChoiceAnimation();
	CGameObject::Render();
}

CKnight::CKnight()
{
	this->currentAniID = (int)KnightAniId::walkRight;
	visible = true;
	health = KNIGHT_HEALTH;
}
