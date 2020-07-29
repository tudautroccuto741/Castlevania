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
#define SIMON_FALL_GRAVITY					0.012f 
#define SIMON_JUMP_GRAVITY					0.0012f
#define SIMON_MAX_SPEED_WITH_JUMP_GRAVITY	0.26f		// max fall down speed can get by jump gravity

#define SIMON_MAX_SPEED_Y						1.8f


#define SIMON_UNTOUCHABLE_TIME				5000
#define SIMON_FLICKERING_TIME				1000
#define SIMON_ATTACK_TIME					450
#define SIMON_DEFAULT_HEALTH				16
#define SIMON_LIFES							3
#define SIMON_HEARTS						5
#define SIMON_TIME_TO_DIE					2000

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
	idleGoingUpStairsLeft,
	IDGoingUpStairsRight,
	IDGoingUpStairsLeft,
	idleGoingDownStairsLeft,
	idleGoingDownStairsRight,
	IDGoingDownStairsLeft,
	IDGoingDownStairsRight,
	IDAttackingOnStairsUpRight,
	IDAttackingOnStairsUpLeft,
	IDAttackingOnStairsDownLeft,
	IDAttackingOnStairsDownRight,
	IDBeAttackingRight,
	IDBeAttackingLeft,
	IDDyingRight,
	IDDyingLeft,
	IDFlickeringRight,
	IDFlickeringLeft
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
	stateGoingUpStairsRight = 108,
	stateGoingDownStairsLeft = 109,
	stateBeHitRight = 110,
	stateBeHitLeft = 111,
	stateDyingRight = 112,
	stateDyingLeft = 113
};

class CSimon : public CGameObject
{
	int untouchable;
	int secondWeapon;
	int stairs; // 1 going up stairs, -1 going down, 0 not in
	int heart;
	int life;
	int score;
	int sceneID;

	bool controllable;
	bool isJumping;
	bool isAttacking;
	bool beHit;
	bool isUsingweapon;
	bool isSitting;
	bool isInBridge; // simon in a bridge
	bool isDying;
	bool flickering;
	float vxDefault = 0;
	int states;


	DWORD startTimeAttack;
	DWORD untouchable_start;
	DWORD start_die;
	DWORD flicker_time;

	DWORD freezeTime;
	DWORD startFreezeTime;

	CWhip *whip;
	CWeapons *weapons;

	vector<LPGAMEOBJECT> ovlObjects;
	vector<LPGAMEOBJECT> objects;

	static CSimon * __instance;
public:
	bool freezing;
	bool isBoss = false;


	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) override;
	void Render() override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;

	void SetState(int state);
	int GetState() { return this->states; }

	void SetFreezing(bool freez) { this->freezing = freez; }
	bool GetFreezing() { return this->freezing; }

	bool GetJumping() { return this->isJumping; }

	void SetVisible(bool visible);
	
	bool IsInBridge(){ return this->isInBridge; }

	void StartUntouchable();
	int GetUntouchable() { return this->untouchable; }

	void Idle();
	void WalkingRight();
	void WalkingLeft();
	void Flickering();
	void Sitting();
	void Jumping();
	void StandUp();
	void Whipping();
	void UseWeapon();
	void ChoiceAnimation();
	void GoingUpStairs();
	void GoingDownStairs();
	void BeHit();
	void Overlapping();
	void OnStairs();
	void Dying();
	void Revive();

	int GetSecondWeapons() { return this->secondWeapon; }
	void SetSecondaryWeapon(int weapon) { this->secondWeapon = weapon; }
	int GetHeart() { return heart; }
	int GetLife() { return life; }
	int GetScore() { return score; }
	void SetScore(int _score) { score += _score; }


	DWORD GetTimeStar() { return startTimeAttack; }
	CSimon();
	~CSimon();
	static CSimon * GetInstance();
};
