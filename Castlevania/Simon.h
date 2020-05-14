#pragma once
#include "GameObject.h"
#include "Animations.h"
#include "Whip.h"
#include "Weapons.h"
#include "StairsUp.h"
#include "StairsDown.h"

#define SIMON_IDLE_BBOX_WIDTH				32.0f
#define SIMON_IDLE_BBOX_HEIGHT				62.0f
#define SIMON_SIT_BBOX_WIDTH				32.0f
#define SIMON_SIT_BBOX_HEIGHT				46.0f
#define SIMON_DIE_BBOX_WIDTH				64.0f
#define SIMON_DIE_BBOX_HEIGHT				30.0f


#define SIMON_WALKING_SPEED					0.15f
#define SIMON_JUMP_SPEED_Y					0.4f
#define SIMON_IS_PUSHED_Y					0.25f
#define SIMON_IS_PUSHED_X					0.1f
#define SIMON_GRAVITY						0.001f
#define SIMON_UNTOUCHABLE_TIME				5000
#define SIMON_ATTACK_TIME					450

enum class SimonAniId
{
	idleGoRight,
	idleGoLeft,
	walkRight,
	walkLeft,
	IDSitRight,
	IDSitLeft,
	IDSitAndWhippingRight,
	IDSitAndWhippingLeft,
	IDWhippingRight,
	IDWhippingLeft,
	idleGoingUpStairsRight,
	IDGoingUpStairsRight,
	idleGoingDownStairsLeft,
	IDGoingDownStairsLeft,
	IDAttackingOnStairsRight,
	IDAttackingOnStairsLeft,
	IDBeAttackingRight,
	IDBeAttackingLeft
};

enum class SimonStateID
{
	stateIdle = 101,
	stateWalkingRight = 102,
	stateWalkingLeft = 103,
	stateJump = 104, 
	stateSit = 105,
	stateWhipping = 106,
	stateUseWeapon = 107,
	stateJumpingAndWhipping = 108,
	stateGoingUpStairsRight = 109,
	stateGoingDownStairsLeft = 110,
	stateBeHitRight = 111,
	stateBeHitLeft = 112
};

class CSimon : public CGameObject
{
	int untouchable;
	int secondWeapon;
	int states;
	int stairs; // 1 going up stairs, -1 going down
	bool isJumping;
	bool isAttacking;
	bool beHit;
	bool isUsingweapon;
	bool isSitting;
	bool canGoingUp;
	bool canGoingDown;
	

	DWORD startTimeAttack;
	DWORD untouchable_start;


	CWhip *whip;
	CWeapons *weapons;


	static CSimon * __instance;
public:

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) override;
	void Render() override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;

	void SetState(int state);
	int GetState() { return this->states; }
	void SetVisible(bool visible);
	
	void SetOnStairs(int onStairs) { this->stairs = onStairs; }
	int IsOnStairs(){ return this->stairs; }
	bool CanGoingUp(){ return this->canGoingUp; }
	bool CanGoingDown() { return this->canGoingDown; }

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void WalkingRight();
	void WalkingLeft();
	void Sitting();
	void Jumping();
	void StandUp();
	void Whipping();
	void UseWeapon();
	void ChoiceAnimation();
	void GoingUpStairs();
	void GoingDownStairs();
	void BeHit();

	int GetSecondWeapons() { return this->secondWeapon; }

	DWORD GetTimeStar() { return startTimeAttack; }
	CSimon();
	~CSimon();
	static CSimon * GetInstance();
};
