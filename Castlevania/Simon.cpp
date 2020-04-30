#include "Simon.h"
#include <algorithm>
#include "debug.h"
#include "Game.h"
#include "Brick.h"
#include "Candle.h"
#include "Flame.h"
#include "HeartItem.h"
#include "WhipItem.h"
#include "KnifeItem.h"
#include "Portal.h"


void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);

	vy += SIMON_GRAVITY * dt;

	if (vx < 0 && x < 0) x = 0;

	//jumping
	if (isJumping)
	{
		vy += SIMON_GRAVITY * this->dt;
	}
	// Attacking
	// check attack state
	if (startTimeAttack != 0)
	{
		if (isAttacking && GetTickCount() - startTimeAttack > SIMON_ATTACK_TIME)
		{
			isAttacking = false;
			whip->SetVisible(false);
			if (isUsingweapon)
			{
				isUsingweapon = false;
			}
		}
	
		/*if (isUsingweapon)
		{
			if (animations->Get(currentAniID)->GetCurrentFrame() == 2)
			{
				this->weapon->ChoiceWeapon(secondWeapon);
			}
		}*/
		
		
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
				if (e->ny < 0)
				{
					if (isJumping)
					{
						isJumping = false;
					}
					y += ny * 0.4f;
					vy = 0;
				}
			}
			else if (dynamic_cast<CWhipItem *>(e->obj))
			{

				if (e->nx != 0 || e->ny != 0)
				{
					this->whip->LvUp();
					e->obj->SetVisible(false);
				}
				if (e->ny != 0)	whip->LvUp();
			}
			else if (dynamic_cast<CHeartItem *>(e->obj))
			{
				if (e->nx != 0 || e->ny != 0)
				{
					e->obj->SetVisible(false);
				}
			}
			else if (dynamic_cast<CKnifeItem *>(e->obj))
			{
				if (e->nx != 0 || e->ny != 0)
				{
					e->obj->SetVisible(false);
					secondWeapon = (int)Weapon::KNIFE;
				}
			}
			else if (dynamic_cast<CPortal *>(e->obj))
			{
				CPortal *p = dynamic_cast<CPortal *>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
		}
	}
	
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];	
	
}

void CSimon::Render()
{
	ChoiceAnimation();
	CGameObject::Render();
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
	if (vy < SIMON_GRAVITY && !isJumping && !isSitting && !isAttacking && !isUsingweapon)
	{
		isJumping = true;
		this->vy = -SIMON_JUMP_SPEED_Y;
	}
}

void CSimon::StandUp()
{
	if (isSitting)
	{
		isSitting = false;
		y -= SIMON_IDLE_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT;
	}
}

void CSimon::UseWeapon()
{
	isAttacking = true;
	isUsingweapon = true;
	startTimeAttack = GetTickCount();
	this->weapon->ChoiceWeapon(secondWeapon);
}

void CSimon::SetVisible(bool isVisble)
{
	CGameObject::SetVisible(visible);
}

void CSimon::SetState(int state)
{
	if (isAttacking) return;
	if (isJumping) return;
	if (isUsingweapon)return;
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
	case (int)SimonStateID::stateWhipping:
		isAttacking = true;
		startTimeAttack = GetTickCount();
		this->whip->SetVisible(true);
		break;
	case (int)SimonStateID::stateUseWeapon:
		UseWeapon();
		break;
	case (int)SimonStateID::stateIdle:
		vx = 0;
		isAttacking = false;
		isUsingweapon = false;
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
		right = x + SIMON_SIT_BBOX_WIDTH;
		bottom = y + SIMON_SIT_BBOX_HEIGHT;
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
	weapon = CWeapons::GetInstance();
	isJumping = false;
	isSitting = false;
}

CSimon::~CSimon()
{
}