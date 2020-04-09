#include "Simon.h"
#include <algorithm>
#include "debug.h"
#include "Game.h"
#include "Brick.h"


void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);

	vy += SIMON_GRAVITY * dt;

	//jumping

	if (isJumping)
	{
		if (vy > SIMON_MAX_SPEED_JUMP_GRAVITY)
		{
			vy += SIMON_FALL_GRAVITY * this->dt;
			if (isSitting)
			{
				this->StandUp();
			}
		}
		else
		{
			vy += SIMON_GRAVITY * this->dt;
		}
		isJumping = false;
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

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

	}
		
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	
}

void CSimon::Render()
{
	ChoiceAnimation();
	CGameObject::Render();
	CGameObject::RenderBoundingBox();
}

void CSimon::ChoiceAnimation()
{
	if (isJumping)
	{
		if (isSitting)
		{
			currentAniID = (nx > 0) ?
				(int)SimonAniId::IDSitRight :
				(int)SimonAniId::IDSitLeft;
		}
		else
		{
			currentAniID = (nx > 0) ?
				(int)SimonAniId::idleGoRight :
				(int)SimonAniId::idleGoLeft;
		}
	}
	else if (isSitting)
	{
		currentAniID = (nx > 0) ?
			(int)SimonAniId::IDSitRight :
			(int)SimonAniId::IDSitLeft;
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
		isSitting = true;
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
			y -= SIMON_IDLE_BBOX_HEIGHT - 54;
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
	CGameObject::SetState(state);
	switch (state)
	{
	case (int)SimonStateID::stateWalkingRight:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case (int)SimonStateID::stateWalkingLeft:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
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
		this->StandUp();
		isAttacking = false;
		break;
	}
}

void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	if (isSitting)
	{
		if (isJumping)
		{
			right = x + SIMON_SIT_BBOX_WIDTH;
			bottom = y + SIMON_SIT_BBOX_HEIGHT;
		}
		else
		{
			right = x + SIMON_SIT_BBOX_WIDTH;
			bottom = y + SIMON_SIT_BBOX_HEIGHT;
		}
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