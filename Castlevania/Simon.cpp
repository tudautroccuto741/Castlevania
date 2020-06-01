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
#include "BoomerangItem.h"
#include "Bridge.h"
#include "SmallHeart.h"
#include "CameraChangeViewObject.h"
#include "Bat.h"

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);

	vy += SIMON_GRAVITY * dt;

	if (vx < 0 && x < 0) x = 0;

	if (GetTickCount() - untouchable_start > 1000)
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

	if (stairs != 0)
	{
		OnStairs();
		vy = 0;
	}
		
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);
	
	// overlapping
	ovlObjects.clear();

	for (UINT i = 0; i < coObjects->size(); ++i)
	{
		if (this->IsOverlapping(coObjects->at(i)))
		{
			ovlObjects.push_back(coObjects->at(i));
		}
	}
	
	if (ovlObjects.size() != 0)
	{
		Overlapping();
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
				if (stairs!=0)
				{
					x += dx;
				}

				if (e->nx != 0)
				{
					x += nx * 0.4f;
				}
				isInBridge = false;
				
			}
			else if (dynamic_cast<CWhipItem *>(e->obj))
			{
				if (e->nx != 0 || e->ny != 0)
				{
					this->whip->LvUp();
					e->obj->SetVisible(false);
					//TouchingItemRope();
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
			else if (dynamic_cast<CBoomerangItem *>(e->obj))
			{
				if (e->nx != 0 || e->ny != 0)
				{
					e->obj->SetVisible(false);
					secondWeapon = (int)Weapon::BOOMERANG;
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
				else
				{
					x += dx;
				}
			}
			else if (dynamic_cast<CBat *>(e->obj))
			{
				if (untouchable == 0)
				{
					if (e->nx != 0 || e->ny != 0)
					{
						e->obj->Destroy();
						BeHit();
					}
				}
			}
			else if (dynamic_cast<CBridge *>(e->obj))
			{
				if (e->ny < 0)
				{
					y += ny * 0.4;
					isInBridge = true;
					vx = BRIDGE_SPEED;
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
	//TouchingItemRope();
	CGameObject::Render();
}

void CSimon::ChoiceAnimation()
{
	if (isInBridge)
	{
		if (isSitting)
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
		else if (vx != BRIDGE_SPEED)
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
	else
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
		if (stairs == 1)
		{
			currentAniID = (nx > 0) ?
				(int)SimonAniId::IDAttackingOnStairsUpRight :
				(int)SimonAniId::IDAttackingOnStairsUpLeft;
		}
		else if (stairs == -1)
		{
			currentAniID = (nx > 0) ?
				(int)SimonAniId::IDAttackingOnStairsDownRight :
				(int)SimonAniId::IDAttackingOnStairsDownLeft;
		}
		else
		{
			currentAniID = (nx > 0) ?
				(int)SimonAniId::IDWhippingRight :
				(int)SimonAniId::IDWhippingLeft;

		}
	}
	else if (stairs == 1)
	{
		if (vx != 0)
		{
			currentAniID = (nx > 0) ?
				(int)SimonAniId::IDGoingUpStairsRight :
				(int)SimonAniId::IDGoingUpStairsLeft;
		}
		else
		{
			currentAniID = (nx > 0) ?
				(int)SimonAniId::idleGoingDownStairsRight :
				(int)SimonAniId::idleGoingDownStairsLeft;
		}
	}
	else if (stairs == -1)
	{

		if (vx != 0)
		{
			currentAniID = (nx > 0) ?
				(int)SimonAniId::IDGoingUpStairsRight :
				(int)SimonAniId::IDGoingDownStairsLeft;
		}
		else
		{
			currentAniID = (nx > 0) ?
				(int)SimonAniId::idleGoingDownStairsRight :
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
}

//void CSimon::Flicker()
//{
//	if (flicker_start == 0)
//		flicker_start = GetTickCount();
//}
//
//void CSimon::TouchingItemRope()
//{
//	if (flicker_start != 0)
//	{
//		// Animation frame will be rendered with
//		// these 3 colors defined by change the argb value
//		if (this->argb.blue != 0)
//			this->argb.blue = 0;
//
//		else if (argb.green != 0)
//			this->argb.green = 0;
//
//		else
//			this->argb = ARGB();
//	}
//}

void CSimon::Idle()
{                                                                                                                                     
	vx = 0;
	isAttacking = false;
	isUsingweapon = false;
	beHit = false;
	this->StandUp();
}

void CSimon::IdleInBridge()
{
	vx = BRIDGE_SPEED;
	isAttacking = false;
	isUsingweapon = false;
	beHit = false;
	this->StandUp();
}

void CSimon::WalkingRight()
{
	if (stairs == 0)
	{
		this->nx = 1;
		if (!isSitting)
		{
			this->vx = SIMON_WALKING_SPEED * this->nx;
		}
	}
	else
	{
		if (stairs == 1)
		{
			if (nx == 1)
				GoingUpStairs();
			else
				GoingDownStairs();
		}
		else if (stairs == -1)
		{
			if (nx == -1)
				GoingUpStairs();
			else
				GoingDownStairs();
		}
	}
}

void CSimon::WalkingRightInBridge()
{
	this->nx = 1;
	if (!isSitting)
	{
		this->vx = (SIMON_WALKING_SPEED * this->nx);
	}
}

void CSimon::WalkingLeft()
{
	if (stairs == 0)
	{
		this->nx = -1;
		if (!isSitting)
		{
			this->vx = SIMON_WALKING_SPEED*this->nx;
		}
	}
	else
	{
		if (stairs == 1)
		{
			if (nx == 1)
				GoingDownStairs();
			else
				GoingUpStairs();
		}
		else if (stairs == -1)
		{
			if (nx == -1)
				GoingDownStairs();
			else
				GoingUpStairs();
		}
	}
}

void CSimon::WalkingLeftInBridge()
{
	this->nx = -1;
	if (!isSitting)
	{
		this->vx = (SIMON_WALKING_SPEED * this->nx);
	}
}

void CSimon::Sitting()
{
	if (!isSitting && stairs == 0)
	{
		this->isSitting = true;
		this->vx = 0;
		this->y += SIMON_IDLE_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT;
	}
}

void CSimon::SittingInBridge()
{
	if (!isSitting)
	{
		this->isSitting = true;
		this->vx = BRIDGE_SPEED;
		this->y += SIMON_IDLE_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT;
	}
}

void CSimon::Jumping()
{
	if (!isJumping && !isSitting)
	{
		if (stairs == 0)
		{
			isJumping = true;
			this->vy = -SIMON_JUMP_SPEED_Y;
		}
	
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
	if (!isJumping)
	{
		vx = 0;
	}
	isAttacking = true;
	startTimeAttack = GetTickCount();
	this->whip->SetVisible(true);
}

void CSimon::WhippingInBridge()
{
	isAttacking = true;
	startTimeAttack = GetTickCount();
	this->whip->SetVisible(true);
	vx = BRIDGE_SPEED;
}

void CSimon::UseWeapon()
{
	vx = 0;
	isAttacking = true;
	isUsingweapon = true;
	startTimeAttack = GetTickCount();
}

void CSimon::UseWeaponInBridge()
{
	vx = BRIDGE_SPEED;
	isAttacking = true;
	isUsingweapon = true;
	startTimeAttack = GetTickCount();
}

void CSimon::GoingUpStairs()
{
	float xS, yS;
	if (stairs == 0)
	{
		LPGAMEOBJECT objS = NULL;
		for (UINT i = 0; i < ovlObjects.size(); ++i)
		{
			if (dynamic_cast<CStairsUp *>(ovlObjects[i]))
			{
				objS = ovlObjects[i];
				break;
			}
		}
			

		if (objS == NULL) return;

		objS->GetPosition(xS, yS);
		
		if (x != xS)
		{
			x = xS;
			y = yS;
		}
		else
		{
			nx = 1;
			stairs = 1;
		}
	}
	
	else
	{
		if (stairs == -1)
		{
			this->nx = -nx;
			stairs = 1;
		}
		vx = 0.051 * nx;
		vy = -0.051;
		isJumping = false;
		isSitting = false;
	}

	
}

void CSimon::OnStairs()
{
	LPGAMEOBJECT objS = NULL;

	if (stairs == 1)
	{
		for (UINT i = 0; i < ovlObjects.size(); ++i)
			if (dynamic_cast<CStairsDown *>(ovlObjects[i]))
			{
				objS = ovlObjects[i];
				break;
			}

		if (objS == NULL) return;

		float xS, yS;
		objS->GetPosition(xS, yS);
		
		// Has reached the stairs exit
		if (y < yS)
		{
			y = yS - 0.4;
			stairs = 0;
			vx = vy = 0;
		}
	}
	else if (stairs == -1)
	{
		for (UINT i = 0; i < ovlObjects.size(); ++i)
			if (dynamic_cast<CStairsUp *>(ovlObjects[i]))
			{
				objS = ovlObjects[i];
				break;
			}

		if (objS == NULL) return;

		float xS, yS;
		objS->GetPosition(xS, yS);

		// Has reached the stairs exit
		if (y > yS)
		{
			y = yS - 0.4;
			stairs = 0;
			vx = vy = 0;
		}
	}
}

void CSimon::GoingDownStairs()
{
	if (stairs == 0)
	{
		LPGAMEOBJECT objS = NULL;
		for (UINT i = 0; i < ovlObjects.size(); ++i)
			if (dynamic_cast<CStairsDown *>(ovlObjects[i]))
			{
				objS = ovlObjects[i];
				break;
			}
		if (objS == NULL) return;

		float xS, yS;
		objS->GetPosition(xS, yS);
		if (x != xS)
		{
			x = xS;
			y = yS;
		}
		else
		{
			nx = -1;
			stairs = -1;
		}
	}
	else
	{
		if (stairs == 1)
		{
			nx = -nx;
			stairs = -1;
		}
		vx = 0.051 * nx;
		vy = 0.051;
		isJumping = false;
		isSitting = false;
	}
}

void CSimon::BeHit()
{
	if (stairs == 0)
	{
		beHit = true;
		vx = vy = dx = dy = 0;
		this->vx = (-this->nx)*SIMON_IS_PUSHED_X;
		this->vy = -SIMON_IS_PUSHED_Y;
		isJumping = true;
		StartUntouchable();
	}
}

void CSimon::Overlapping()
{
	LPGAMEOBJECT obj;
	for (UINT i = 0; i < ovlObjects.size(); i++)
	{
		obj = ovlObjects[i];
		if (dynamic_cast<CWhipItem *>(obj))
		{
			obj->SetVisible(false);
			this->whip->LvUp();
		}
		else if (dynamic_cast<CHeartItem *>(obj)||dynamic_cast<CSmallHeart *>(obj))
		{
			obj->SetVisible(false);
		}
		else if (dynamic_cast<CKnifeItem *>(obj))
		{
			obj->SetVisible(false);
			secondWeapon = (int)Weapon::KNIFE;
		}
		else if (dynamic_cast<CBoomerangItem *>(obj))
		{
			obj->SetVisible(false);
			secondWeapon = (int)Weapon::BOOMERANG;
		}
		else if (dynamic_cast<CKnight *>(obj))
		{
			if (untouchable == 0)
			{
				BeHit();
			}
		}
		else if (dynamic_cast<CBat *>(obj))
		{
			if (untouchable == 0)
			{
				BeHit();
			}
		}
	}
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
	//if (isInBridge) return;
	if (isInBridge)
	{
		switch (state)
		{
		case (int)SimonStateID::stateWalkingRightInBridge:
			WalkingRightInBridge();
			break;
		case (int)SimonStateID::stateWalkingLeftInBridge:
			WalkingLeftInBridge();
			break;
		case (int)SimonStateID::stateJumpInBridge:
			Jumping();
			break;
		case (int)SimonStateID::stateSitInBridge:
			SittingInBridge();
			break;
		case (int)SimonStateID::stateWhippingInBridge:
			WhippingInBridge();
			break;
		case (int)SimonStateID::stateUseWeaponInBridge:
			UseWeaponInBridge();
			break;
		case (int)SimonStateID::stateIdleInBridge:
			IdleInBridge();
			break;
		}
	}
	else
	{
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
			GoingUpStairs();
			break;
		case (int)SimonStateID::stateGoingDownStairsLeft:
			GoingDownStairs();
			break;
		case (int)SimonStateID::stateBeHitRight:
			beHit = true;
			isAttacking = false;
			break;
		case (int)SimonStateID::stateIdle:
			Idle();
			break;
		}
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
	isInBridge = false;
}

CSimon::~CSimon()
{
}