#pragma once
#include "GameObject.h"
#include "Animations.h"
#include "Whip.h"
#define SIMON_WALKING_SPEED		0.15f
#define SIMON_JUMP_SPEED_Y		0.4f
#define SIMON_GRAVITY			0.1f
#define DEFAULT_TIME_VALUE 1000
enum class SimonAniId
{
	idleGoRight,
	idleGoLeft,
	walkRight,
	walkLeft,
	IDJumpRight,
	IDJumpLeft,
	IDWhipRight,
	IDWhipLeft
	
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
	float x;
	float y;

	float vx;
	float vy;

	int nx;
	//int untouchable;
	
	bool isJumping;
	bool isAttacking;
	bool isUsingweapon;

	DWORD start;
	DWORD time;
	//DWORD untouchable_start;

	CWhip *whip;

	static CSimon * __instance;
public:

	//virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Update(DWORD dt);
	void Render();
	void SetState(int state);	
	//void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	//virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	int GetDirection() { return nx; }
	float GetX() { return x; }
	float GetY() { return y; }
	DWORD GetTimeStar() { return start; }
	CSimon();
	~CSimon();
	static CSimon * GetInstance();
};
