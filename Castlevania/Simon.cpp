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
#include "Knight.h"


void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);

	vy += SIMON_GRAVITY * dt;

	if (vx < 0 && x < 0) x = 0;

	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// Attacking
	// check attack state
	if (startTimeAttack != 0)
	{
		if (isAttacking && GetTickCount() - startTimeAttack > SIMON_ATTACK_TIME)
		{
			isAttacking = false;
			whip->SetVisible(false);
		}

		if (isUsingweapon)
		{
			if (animations->Get(currentAniID)->GetCurrentFrame() == 2)
			{
				this->weapons->ChoiceWeapon(secondWeapon);
				isUsingweapon = false;
			}
		}
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	// is overlapping
	for (UINT i = 0; i < coObjects->size(); ++i)
	{
		float xS, yS;
		if (this->IsOverlapping(coObjects->at(i)))
		{
			coObjects->at(i)->GetPosition(xS, yS);
			if (dynamic_cast<CWhipItem *>(coObjects->at(i)))
			{
				coObjects->at(i)->Destroy();
				this->whip->LvUp();
			}
			else if (dynamic_cast<CHeartItem *>(coObjects->at(i)))
			{
				coObjects->at(i)->Destroy();
			}
			else if (dynamic_cast<CKnifeItem *>(coObjects->at(i)))
			{
				coObjects->at(i)->Destroy();
				secondWeapon = (int)Weapon::KNIFE;
			}
			else if (dynamic_cast<CStairsUp *>(coObjects->at(i)))
			{
				canGoingUp = true;
				if (GetState()==(int)SimonStateID::stateGoingUpStairsRight)
				{
					SetOnStairs(1);
					SetPosition(xS + 10, y);
				}
				if (IsOnStairs() == -1 && canGoingDown == true && (y + SIMON_IDLE_BBOX_HEIGHT >= yS + STAIRS_DOWN_BBOX_HEIGHT))
				{
					SetOnStairs(0);
					canGoingDown = false;
				}
			}
			else if (dynamic_cast<CStairsDown *>(coObjects->at(i)))
			{
				canGoingDown = true;
				if (GetState() == (int)SimonStateID::stateGoingDownStairsLeft)
				{
					SetOnStairs(-1);
					SetPosition(xS - 16, y);
				}
				coObjects->at(i)->GetPosition(xS, yS);
				if (IsOnStairs()==1 && canGoingUp == true && (y + SIMON_IDLE_BBOX_HEIGHT <= yS + STAIRS_DOWN_BBOX_HEIGHT))
				{
					SetOnStairs(0);
					canGoingUp = false;
				}
			}
			else if (dynamic_cast<CKnight *>(coObjects->at(i)))
			{
				if (untouchable == 0)
				{
					BeHit();
				}
			}
		}
	}

	if (IsOnStairs() == 1 || IsOnStairs() == -1)
	{
		vy = 0;
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
					if (isJumping||beHit)
					{
						isJumping = false;
						beHit = false;
					}
					y += ny * 0.4f;
					vy = 0;
				}
				if (GetState() == (int)SimonStateID::stateGoingDownStairsLeft)
				{
					x += dx;
				}
				else
				{
					if (e->nx != 0)
					{
						x += nx * 0.4f;
					}
				}
				
			}
			else if (dynamic_cast<CWhipItem *>(e->obj))
			{
				if (e->nx != 0 || e->ny != 0)
				{
					this->whip->LvUp();
					e->obj->SetVisible(false);
				}
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
			else if (dynamic_cast<CKnight *>(e->obj))
			{
				if (untouchable == 0)
				{
					if (e->nx != 0 || e->ny != 0)
					{
						BeHit();
					}
				}
			}
			else if (dynamic_cast<CPortal *>(e->obj))
			{
				CPortal *p = dynamic_cast<CPortal *>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
				i = coEventsResult.size();
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
	if (beHit)
	{
		currentAniID = (-nx > 0) ?
			(int)SimonAniId::IDBeAttackingRight :
			(int)SimonAniId::IDBeAttackingLeft;
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
		if (IsOnStairs() != 0)
		{
			currentAniID = (nx > 0) ?
				(int)SimonAniId::IDAttackingOnStairsRight:
				(int)SimonAniId::IDAttackingOnStairsLeft;
		}
		else
		{
			currentAniID = (nx > 0) ?
				(int)SimonAniId::IDWhippingRight :
				(int)SimonAniId::IDWhippingLeft;

		}
	}
	else if (IsOnStairs() != 0)
	{
		if (canGoingUp && vx!=0)
		{
			currentAniID = (nx > 0) ?
				(int)SimonAniId::IDGoingUpStairsRight :
				(int)SimonAniId::IDGoingDownStairsLeft;
		}
		else if(canGoingDown && vx != 0)
		{
			currentAniID = (nx > 0) ?
				(int)SimonAniId::IDGoingUpStairsRight :
				(int)SimonAniId::IDGoingDownStairsLeft;
		}
		else
		{
			currentAniID = (nx > 0) ?
				(int)SimonAniId::idleGoingUpStairsRight :
				(int)SimonAniId::idleGoingDownStairsLeft;
		}
	}
	else if (isJumping)
	{
		if (isAttacking)
		{
			currentAniID = (nx > 0) ?
				(int)SimonAniId::IDWhippingRight :
				(int)SimonAniId::IDWhippingLeft;
		}
		else
		{
			currentAniID = (nx > 0) ?
				(int)SimonAniId::IDSitRight :
				(int)SimonAniId::IDSitLeft;
		}
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

void CSimon::WalkingRight()
{
	nx = 1;
	if (isSitting) return;
	vx = SIMON_WALKING_SPEED;
}

void CSimon::WalkingLeft()
{
	nx = -1;
	if (isSitting) return;
	vx = -SIMON_WALKING_SPEED;
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
	if (vy < SIMON_GRAVITY && !isJumping && !isSitting)
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

void CSimon::Whipping()
{
	isAttacking = true;
	startTimeAttack = GetTickCount();
	this->whip->SetVisible(true);
}

void CSimon::UseWeapon()
{
	isAttacking = true;
	isUsingweapon = true;
	startTimeAttack = GetTickCount();
}

void CSimon::GoingUpStairs()
{
	nx = 1;
	vx = SIMON_WALKING_SPEED;
	vy = -0.15;
	isJumping = false;
	isSitting = false;
}

void CSimon::GoingDownStairs()
{
	nx = -1;
	vx = -SIMON_WALKING_SPEED;
	vy = 0.15;
	isJumping = false;
	isSitting = false;
}

void CSimon::BeHit()
{
	beHit = true;
	vx = vy = dx = dy = 0;
	this->vx = (-this->nx)*SIMON_IS_PUSHED_X;
	this->vy = -SIMON_IS_PUSHED_Y;
	isJumping = true;
	StartUntouchable();
}

void CSimon::SetVisible(bool isVisble)
{
	CGameObject::SetVisible(visible);
}

void CSimon::SetState(int state)
{
	if (isAttacking) return;
	if (isUsingweapon)return;
	if (beHit) return;
	switch (state)
	{
	case (int)SimonStateID::stateWalkingRight:
		WalkingRight();
		break;
	case (int)SimonStateID::stateWalkingLeft:
		WalkingLeft();
		break;
	case (int)SimonStateID::stateJump:
		Jumping();
		break;
	case (int)SimonStateID::stateSit:
		Sitting();
		break;
	case (int)SimonStateID::stateWhipping:
		Whipping();
		break;
	case (int)SimonStateID::stateUseWeapon:
		UseWeapon();
		break;
	case (int)SimonStateID::stateGoingUpStairsRight:
		if (canGoingUp || IsOnStairs()==1 || IsOnStairs() == -1)
		{
			GoingUpStairs();
			break;
		}
	case (int)SimonStateID::stateGoingDownStairsLeft:
		if (canGoingDown || IsOnStairs() == 1 || IsOnStairs() == -1)
		{
			GoingDownStairs();
			break;
		}
	case (int)SimonStateID::stateBeHitRight:
	{
		beHit = true;
		canGoingDown = false;
		canGoingUp = false;
		isAttacking = false;
	}
	case (int)SimonStateID::stateIdle:
		vx = 0;
		isAttacking = false;
		isUsingweapon = false;
		beHit = false;
		this->StandUp();
		break;
	}
	states = state;
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
	untouchable = 0;
	weapons = CWeapons::GetInstance();
	isJumping = false;
	isSitting = false;
}

CSimon::~CSimon()
{
}