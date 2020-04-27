#pragma once
#include "GameObject.h"
#include "Animations.h"
#include "Whip.h"
#include "Weapons.h"

#define SIMON_IDLE_BBOX_WIDTH				32.0f
#define SIMON_IDLE_BBOX_HEIGHT				62.0f
#define SIMON_SIT_BBOX_WIDTH				32.0f
#define SIMON_SIT_BBOX_HEIGHT				46.0f


#define SIMON_WALKING_SPEED					0.12f
#define SIMON_JUMP_SPEED_Y					0.4f
#define SIMON_GRAVITY						0.0012f
#define SIMON_FALL_GRAVITY					0.012f
#define DEFAULT_TIME_VALUE					1000
#define SIMON_UNTOUCHABLE_TIME				5000

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
	IDWhippingLeft
	
};
enum class SimonStateID
{
	stateIdle = 101,
	stateWalkingRight = 102,
	stateWalkingLeft = 103,
	stateJump = 104, 
	stateSit = 105,
	stateWhipping = 106,
	stateUseWeapon = 107
};

class CSimon : public CGameObject
{
	int untouchable;
	int secondWeapon;
	
	bool isJumping;
	bool isAttacking;
	bool isUsingweapon;
	bool isSitting;
	bool isMovable;
	

	DWORD startTimeAttack;
	DWORD untouchable_start;

	CWhip *whip;
	CWeapons *weapon;


	//vector<LPGAMEOBJECT> ovObjects;		// overlapping objects
	//vector<LPGAMEOBJECT>* coObjects;	// for saving the coObjects at the current frame to manipulate easily

	static CSimon * __instance;
public:

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) override;
	void Render() override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;

	void SetState(int state);	
	void SetVisible(bool visible);

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Sitting();
	void Jumping();
	void StandUp();
	void UseWeapon();
	void ChoiceAnimation();

	int GetSecondWeapons() { return this->secondWeapon; }

	DWORD GetTimeStar() { return startTimeAttack; }
	CSimon();
	~CSimon();
	static CSimon * GetInstance();
};
