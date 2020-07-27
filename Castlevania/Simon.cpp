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
#include "Boomerang.h"
#include "SecretBrick.h"
#include "Crown.h"
#include "WhiteMoneyBag.h"
#include "IIitem.h"
#include "RedMoneyBag.h"
#include "Meat.h"
#include "AquafinaItem.h"
#include "AxeItem.h"
#include "Flea.h"
#include "SpawnFlea.h"
#include "Monkey.h"
#include "Raven.h"
#include "Skeleton.h"
#include "BoneWeapon.h"
#include "Board.h"
#include "Numbers.h"


void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);

	vy += SIMON_GRAVITY * dt;

	if (vx < 0 && x < 0) x = 0;

	// untouchable
	if (untouchable_start > 0)
	{
		if (untouchable == 1 && GetTickCount() - untouchable_start > 2000)
		{
			untouchable_start = 0;
			untouchable = 0;
		}
	}

	// Attacking
	// check attack state
	if (startTimeAttack > 0)
	{
		if (isAttacking && GetTickCount() - startTimeAttack > SIMON_ATTACK_TIME)
		{
			isAttacking = false;
			whip->SetVisible(false);
			startTimeAttack = 0;
		}

		if (isUsingweapon)
		{
			if (animations->Get(currentAniID)->GetCurrentFrame() == 2)
			{
				this->weapons->ChoiceWeapon(secondWeapon);
				isUsingweapon = false;
				if (secondWeapon == (int)Weapon::WATCH)
				{
					if (GetTickCount() - startFreezeTime > freezeTime)
					{
						for (UINT i = 0; i < this->objects.size(); ++i)
							this->objects[i]->SetFreezing(false);

						this->freezing = false;
					}
				}
			}
		}
	}

	if (stairs != 0)
	{
		OnStairs();
		vy = 0;
	}

	// Dying and revive
	if (health <= 0 && !isJumping && start_die == 0)	// Simon has landed on the ground
	{		
		Dying();
	}	
	if (GetTickCount() - start_die >= SIMON_TIME_TO_DIE && isDying)
	{
		isDying = false;
		Revive();
		start_die = 0;
	}

	if (flicker_time > 0)
	{
		vx = vxDefault;
		Flickering();
	}

	// show a flea
	
	if (sceneID == 3)
	{
		if (x <= POSITION_FLEA_TO_VISIBLE 
			&& CSpawnFlea::GetInstance()->GetFlea((int)Monsters::FLEA)->GetVisible() == false 
			&& CSpawnFlea::GetInstance()->GetFlea((int)Monsters::FLEA)->GetHealth()>=3 
			&& y > CCameraChangeViewObject::GetInstance()->GetY())
		{
			CSpawnFlea::GetInstance()->ShowFlea();
		}
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

			if (dynamic_cast<CBrick *>(e->obj)
				|| dynamic_cast<CSecretBrick *>(e->obj))
			{
				vxDefault = 0;
				if (e->ny < 0)
				{
					if (isJumping || beHit)
					{
						isJumping = false;
						beHit = false;
					}
					y += ny * 0.4f;
					vy = 0;
				}
				if (stairs != 0)
				{
					x += dx;
					beHit = false;
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
					flickering = true;
					flicker_time = GetTickCount();
					this->whip->LvUp();
					e->obj->SetVisible(false);
				}
			}
			else if (dynamic_cast<CHeartItem *>(e->obj))
			{
				if (e->nx != 0 || e->ny != 0)
				{
					e->obj->SetVisible(false);
					heart += 5;
				}
			}
			else if (dynamic_cast<CSmallHeart *>(e->obj))
			{
				if (e->nx != 0 || e->ny != 0)
				{
					e->obj->SetVisible(false);
					heart += 1;
				}
			}
			else if (dynamic_cast<CIIitem *>(e->obj)
				|| dynamic_cast<CMeat *>(e->obj))
			{
				if (e->nx != 0 || e->ny != 0)
				{
					e->obj->SetVisible(false);
					/*SetHealth(this->health + 2);*/
				}
			}
			else if (dynamic_cast<CCrown *>(e->obj)
				|| dynamic_cast<CWhiteMoneyBag *>(e->obj))
			{
				e->obj->SetVisible(false);
				CNumbers::GetInstance()->ShowNumbers((int)NumberAniID::IDLE2, e->obj->x+32, e->obj->y+32);
			}
			else if (dynamic_cast<CRedMoneyBag *>(e->obj))
			{
				e->obj->SetVisible(false);
				CNumbers::GetInstance()->ShowNumbers((int)NumberAniID::IDLE1, e->obj->x + 32, e->obj->y + 32);
			}
			else if (dynamic_cast<CKnifeItem *>(e->obj))
			{
				if (e->nx != 0 || e->ny != 0)
				{
					e->obj->SetVisible(false);
					secondWeapon = (int)Weapon::KNIFE;
					CBoard::GetInstance()->SetWeapon((int)Item::KNIFE);

				}
			}
			else if (dynamic_cast<CAquafinaItem *>(e->obj))
			{
				if (e->nx != 0 || e->ny != 0)
				{
					e->obj->SetVisible(false);
					secondWeapon = (int)Weapon::AQUAFINA;
					CBoard::GetInstance()->SetWeapon((int)Item::AQUAFINA);
				}
			}
			else if (dynamic_cast<CAxeItem *>(e->obj))
			{
				if (e->nx != 0 || e->ny != 0)
				{
					e->obj->SetVisible(false);
					secondWeapon = (int)Weapon::AXE;
					CBoard::GetInstance()->SetWeapon((int)Item::AXE);
				}
			}
			else if (dynamic_cast<CBoomerangItem *>(e->obj))
			{
				if (e->nx != 0 || e->ny != 0)
				{
					e->obj->SetVisible(false);
					secondWeapon = (int)Weapon::BOOMERANG;
					CBoard::GetInstance()->SetWeapon((int)Item::BOOMERANG);

				}
			}
			else if (dynamic_cast<CKnight *>(e->obj)
				|| dynamic_cast<CFlea *>(e->obj)
				|| dynamic_cast<CMonkey *>(e->obj)
				|| dynamic_cast<CSkeleton *>(e->obj))
			{
				if (untouchable == 0)
				{
					if (e->nx != 0 || e->ny != 0)
					{
						this->nx = (e->nx != 0) ?
							-(e->nx) :
							-(e->obj->GetDirection());
						BeHit();
						StartUntouchable();
					}
				}
				else
				{
					x += dx;
				}
			}
			else if (dynamic_cast<CBat *>(e->obj)
			|| dynamic_cast<CRaven *>(e->obj))
			{
				if (untouchable == 0)
				{
					if (e->nx != 0 || e->ny != 0)
					{
						if (stairs == 0)
						{
							this->nx = (e->nx != 0) ?
								-(e->nx) :
								-(e->obj->GetDirection());
							BeHit();
						}
						e->obj->Destroy();
						StartUntouchable();
					}
				}
			}
			else if (dynamic_cast<CBridge *>(e->obj))
			{
				if (e->ny < 0)
				{
					if (isJumping || beHit)
					{
						isJumping = false;
						beHit = false;
					}
					y += ny * 0.4;
					vy = 0;
					isInBridge = true;
					vxDefault = e->obj->vx;
					vx = vxDefault;
				}
				else
				{
					isInBridge = false;
					vxDefault = 0;
				}
			}
			else if (dynamic_cast<CPortal *>(e->obj))
			{
				CPortal *p = dynamic_cast<CPortal *>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
				i = coEventsResult.size();
				this->sceneID += 1;
			}
		}
	}
	
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CSimon::Render()
{
	ChoiceAnimation();
	if (untouchable == 1)
	{
		this->alpha = rand() % 255;
	}
	else
	{
		this->alpha = 255;
		
	}
	animations->Get(currentAniID)->Render(x, y, alpha);
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
				(int)SimonAniId::idleGoingUpStairsRight :
				(int)SimonAniId::idleGoingUpStairsLeft;
		}
	}
	else if (stairs == -1)
	{

		if (vx != 0)
		{
			currentAniID = (nx > 0) ?
				(int)SimonAniId::IDGoingDownStairsRight :
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
	else if (flickering)
	{
		currentAniID = (nx > 0) ?
			(int)SimonAniId::IDFlickeringRight :
			(int)SimonAniId::IDFlickeringLeft;
	}
	else if (vx != vxDefault)
	{
		currentAniID = (nx > 0) ?
			(int)SimonAniId::walkRight :
			(int)SimonAniId::walkLeft;
	}
	else if (health <= 0)
	{
		currentAniID = (nx > 0) ?
			(int)SimonAniId::IDDyingRight :
			(int)SimonAniId::IDDyingLeft;
	}
	else
	{
		currentAniID = (nx > 0) ?
			(int)SimonAniId::idleGoRight :
			(int)SimonAniId::idleGoLeft;
	}
}

void CSimon::Idle()
{                                                                                                                                     
	vx = vxDefault;
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
			this->vx = SIMON_WALKING_SPEED * this->nx + vxDefault;
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

void CSimon::WalkingLeft()
{
	if (stairs == 0)
	{
		this->nx = -1;
		if (!isSitting)
		{
			this->vx = SIMON_WALKING_SPEED*this->nx + vxDefault;
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

void CSimon::Flickering()
{
	if (flickering && GetTickCount()-flicker_time >= SIMON_FLICKERING_TIME)
	{
		isAttacking = false;
		isJumping = false;
		flickering = false;
		flicker_time = 0;
	}
}

void CSimon::Sitting()
{
	if (!isSitting && stairs == 0 && !isJumping)
	{
		this->isSitting = true;
		this->vx = vxDefault;
		this->y += SIMON_IDLE_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT;
	}
}

void CSimon::Jumping()
{
	if (!isJumping && !isSitting)
	{
		
		if (stairs == 0)
		{
			if (IsInBridge())
			{
				vxDefault = 0;
			}
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
		vx = vxDefault;
	}
	isAttacking = true;
	startTimeAttack = GetTickCount();
	this->whip->SetVisible(true);
}

void CSimon::UseWeapon()
{
	vx = vxDefault;
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
			this->nx = objS->GetDirection();
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
	beHit = false;
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
		if (y < yS && this->nx != objS->GetDirection())
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
		if (y > yS && this->nx != objS->GetDirection())
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
			nx = objS->GetDirection();
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
	if (health <= 0)
	{
		return;
	}
	if (stairs == 0)
	{
		beHit = true;
		//vx = vy = dx = dy = 0;
		this->vx = (-this->nx)*SIMON_IS_PUSHED_X;
		this->vy = -SIMON_IS_PUSHED_Y;
		isJumping = true;
		untouchable_start = 0;
		health -= 2;
	}
}

void CSimon::Dying()
{
	isDying = true;
	start_die = GetTickCount();
	vx = 0;
	isJumping = false;
	isAttacking = false;
	beHit = false;
	isUsingweapon = false;
	isSitting = false;
	isInBridge = false;
}

void CSimon::Revive()
{
	this->health = SIMON_DEFAULT_HEALTH;
	life = life - 1;
	this->SetVisible(true);
	float xS, yS;
	if (sceneID == 1)
	{
		SetPosition(80, 255);
	}
	else if(sceneID == 2)
	{
		SetPosition(560, 672);
	}
	else if (sceneID == 3)
	{
		SetPosition(1486, 640);
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
			flickering = true;
			flicker_time = GetTickCount();
			obj->SetVisible(false);
			this->whip->LvUp();
		}
		else if (dynamic_cast<CHeartItem *>(obj))
		{
			obj->SetVisible(false);
			heart += 5;
		}
		else if (dynamic_cast<CSmallHeart *>(obj))
		{
			obj->SetVisible(false);
			heart += 1;
		}
		else if (dynamic_cast<CCrown *>(obj)
			|| dynamic_cast<CIIitem *>(obj)
			|| dynamic_cast<CWhiteMoneyBag *>(obj)
			|| dynamic_cast<CRedMoneyBag *>(obj)
			|| dynamic_cast<CMeat *>(obj))
		{
			obj->SetVisible(false);
		}
		else if (dynamic_cast<CKnifeItem *>(obj))
		{
			obj->SetVisible(false);
			secondWeapon = (int)Weapon::KNIFE;
			CBoard::GetInstance()->SetWeapon((int)Item::KNIFE);
		}
		else if (dynamic_cast<CBoomerangItem *>(obj))
		{
			obj->SetVisible(false);
			secondWeapon = (int)Weapon::BOOMERANG;
			CBoard::GetInstance()->SetWeapon((int)Item::BOOMERANG);
		}
		else if (dynamic_cast<CAquafinaItem *>(obj))
		{
			obj->SetVisible(false);
			secondWeapon = (int)Weapon::AQUAFINA;
		}
		else if (dynamic_cast<CAxeItem *>(obj))
		{
			obj->SetVisible(false);
			secondWeapon = (int)Weapon::AXE;
		}
		else if (dynamic_cast<CKnight *>(obj)
			||dynamic_cast<CFlea *>(obj)
			|| dynamic_cast<CMonkey *>(obj))
		{
			if (untouchable == 0)
			{
				BeHit();
				StartUntouchable();
			}
		}
		else if (dynamic_cast<CBat *>(obj))
		{
			if (untouchable == 0)
			{
				BeHit();
				StartUntouchable();
				obj->Destroy();
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
	if (isDying)return;
	if (isAttacking) return;
	if (isUsingweapon)return;
	if (beHit) return;
	if (flickering)return;
	/*if (isJumping) return;*/
	switch (state)
	{
	case (int)SimonStateID::stateWalkingRight:
		if (!isJumping)
		{
			WalkingRight();
		}
		break;
	case (int)SimonStateID::stateWalkingLeft:
		if (!isJumping)
		{
			WalkingLeft();
		}
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
	case (int)SimonStateID::stateIdle:
		Idle();
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
	if (health <= 0)
	{
		right = x + SIMON_DIE_BBOX_WIDTH;
		bottom = y + SIMON_DIE_BBOX_HEIGHT;
	}
}

void CSimon::StartUntouchable() 
{ 
	untouchable = 1;
	if (untouchable_start == 0)
	{
		untouchable_start = GetTickCount();
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
	flickering = false;
	flicker_time = 0;
	health = SIMON_DEFAULT_HEALTH;
	life = SIMON_LIFES;
	heart = SIMON_HEARTS;
	isDying = false;
	start_die = 0;
	sceneID = CGame::GetInstance()->GetCurrentSceneID();
}

CSimon::~CSimon()
{
}