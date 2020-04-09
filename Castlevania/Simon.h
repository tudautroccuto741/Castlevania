#pragma once
#include "GameObject.h"
#include "Animations.h"
#include "Whip.h"

#define SIMON_IDLE_BBOX_WIDTH				32.0f
#define SIMON_IDLE_BBOX_HEIGHT				62.0f
#define SIMON_SIT_BBOX_WIDTH				32.0f
#define SIMON_SIT_BBOX_HEIGHT				46.0f
#define SIMON_JUMP_CROUCH_DISTANCE			54.0f


#define SIMON_WALKING_SPEED					0.12f
#define SIMON_JUMP_SPEED_Y					0.4f
#define SIMON_GRAVITY						0.012f
#define SIMON_GRAVITY_ONGROUND				0.2f
#define SIMON_FALL_GRAVITY					0.012f
#define SIMON_MAX_SPEED_JUMP_GRAVITY		-0.26f
#define SIMON_MAX_SPEED_Y					1.8f

#define DEFAULT_TIME_VALUE 1000
#define SIMON_UNTOUCHABLE_TIME 5000

enum class SimonAniId
{
	idleGoRight,
	idleGoLeft,
	walkRight,
	walkLeft,
	IDSitRight,
	IDSitLeft,
	IDWhippingRight,
	IDWhippingLeft
	
};
enum class SimonStateID
{
	IDTex = 100,
	stateIdle = 101,
	stateWalkingRight = 102,
	stateWalkingLeft = 103,
	stateJump = 104, 
	stateSit = 105,
	stateWhip = 106
};

class CSimon : public CGameObject
{
	int untouchable;
	
	bool isJumping;
	bool isAttacking;
	bool isUsingweapon;
	bool isSitting;
	

	DWORD startTimeAttack;
	DWORD untouchable_start;

	CWhip *whip;

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

	void Attacking();
	void Sitting();
	void Jumping();
	void StandUp();
	void ChoiceAnimation();


	DWORD GetTimeStar() { return startTimeAttack; }
	CSimon();
	~CSimon();
	static CSimon * GetInstance();
};
