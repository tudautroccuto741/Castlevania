#include "Simon.h"
#include <algorithm>
#include "debug.h"
#include "Game.h"
#include "Brick.h"
#include "Candle.h"


void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);

	vy += SIMON_GRAVITY * dt;

	//jumping

	if (vx > 0 && x > 290) x = 290;
	if (vx < 0 && x < 0) x = 0;

	if (isJumping)
	{
		vy += SIMON_GRAVITY * this->dt;
	}
	// Attacking
	// check attack state
	if (startTimeAttack != 0)
	{
		if (isAttacking && GetTickCount() - startTimeAttack > 450)
		{
			Attacking();
			isAttacking = false;
			whip->SetVisible(false);
		}
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);
	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	float min_tx, min_ty, nx = 0, ny;
	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

	}
	// collision
	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];
		// collision with brick

		if (dynamic_cast<CBrick *>(e->obj))
		{
			if (e->ny < 0)
			{
				if (isJumping)
				{
					this->StandUp();
					isJumping = false;
					vy = 0;
				}
			}
		}
		// collision with candle

		if (dynamic_cast<CCandle *>(e->obj))
		{
			// Ignore other collisions
			if (e->nx != 0)	x += (1 - min_tx) * dx;
			if (e->ny != 0)	y += (1 - min_ty) * dy;
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	
}

void CSimon::Render()
{
	ChoiceAnimation();
	CGameObject::Render();
	// CGameObject::RenderBoundingBox();
}

void CSimon::ChoiceAnimation()
{
	if (isJumping)
	{
		currentAniID = (nx > 0) ?
			(int)SimonAniId::IDSitRight :
			(int)SimonAniId::IDSitLeft;
	}
	else if (isSitting)
	{
		if (isAttacking)
		{
			currentAniID = (nx > 0) ?
				(int)SimonAniId::IDSitAndWhippingRight :
				(int)SimonAniId::IDSitAndWhippingLeft;
		}
		else
		{
			currentAniID = (nx > 0) ?
				(int)SimonAniId::IDSitRight :
				(int)SimonAniId::IDSitLeft;
		}
	}
	else if (isAttacking)
	{
		currentAniID = (nx > 0) ?
			(int)SimonAniId::IDWhippingRight :
			(int)SimonAniId::IDWhippingLeft;
	}

	else if (vx != 0)
	{
		currentAniID = (nx > 0) ?
			(int)SimonAniId::walkRight :
			(int)SimonAniId::walkLeft;
	}
	else
	{
		currentAniID = (nx > 0) ?
			(int)SimonAniId::idleGoRight :
			(int)SimonAniId::idleGoLeft;
	}
}

void CSimon::Attacking()
{
	if (startTimeAttack == 0)
	{
		startTimeAttack = GetTickCount();
		whip->SetDirection(nx);
	}
}

void CSimon::Sitting()
{
	if (!isSitting)
	{
		this->isSitting = true;
		this->vx = 0;
		this->y += SIMON_IDLE_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT;
	}
}

void CSimon::Jumping()
{
	if (vy < SIMON_GRAVITY && !isJumping && !isSitting && !isAttacking)
	{
		isJumping = true;
		// isSitting = true;
		this->vy = -SIMON_JUMP_SPEED_Y;
	}
}

void CSimon::StandUp()
{
	if (!isJumping)
	{
		if (isSitting)
		{
			isSitting = false;
			y -= SIMON_IDLE_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT;
		}
	}
	else
	{
		if (isSitting)
		{
			isSitting = false;
			y -= SIMON_IDLE_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT;
		};
	}
}

void CSimon::SetVisible(bool isVisble)
{
	CGameObject::SetVisible(visible);
}

void CSimon::SetState(int state)
{
	if (isAttacking) return;
	if (isJumping) return;
	CGameObject::SetState(state);
	switch (state)
	{
	case (int)SimonStateID::stateWalkingRight:
		nx = 1;
		if (isSitting) return;
		vx = SIMON_WALKING_SPEED;
		break;
	case (int)SimonStateID::stateWalkingLeft:
		nx = -1;
		if (isSitting) return;
		vx = -SIMON_WALKING_SPEED;
		break;
	case (int)SimonStateID::stateJump:
		Jumping();
		break;
	case (int)SimonStateID::stateSit:
		Sitting();
		break;
	case (int)SimonStateID::stateWhip:
		isAttacking = true;
		startTimeAttack = GetTickCount();
		whip->SetVisible(true);
		break;
	case (int)SimonStateID::stateIdle:
		vx = 0;
		isAttacking = false;
		this->StandUp();
		break;
	}
}

void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	if (isSitting)
	{
		/*if (isJumping)
		{
			right = x + SIMON_SIT_BBOX_WIDTH;
			bottom = y + SIMON_SIT_BBOX_HEIGHT;
		}
		else
		{*/
			right = x + SIMON_SIT_BBOX_WIDTH;
			bottom = y + SIMON_SIT_BBOX_HEIGHT;
		//}
	}
	else
	{
		right = x + SIMON_IDLE_BBOX_WIDTH;
		bottom = y + SIMON_IDLE_BBOX_HEIGHT;
	}
}


CSimon * CSimon::__instance = NULL;
CSimon* CSimon::GetInstance()
{
	if (__instance == NULL) __instance = new CSimon();
	return __instance;
}

CSimon::CSimon()
{
	SetState((int)SimonStateID::stateIdle);
	visible = true;
	whip = CWhip::GetInstance();
	isJumping = false;
	isSitting = false;
}

CSimon::~CSimon()
{
}