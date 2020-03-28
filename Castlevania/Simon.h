#pragma once
#include "GameObject.h"
#include "Animations.h"

#define SIMON_WALKING_SPEED		0.15f
#define SIMON_JUMP_SPEED_Y		0.4f
#define SIMON_GRAVITY			0.1f

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
enum class SimonID
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

	float x = 0;
	float y = 0;

	float vx = 0;
	float vy = 0;

	int nx = 1;
	bool isJumping;
	bool isAttacking;

	DWORD a = GetTickCount();

	static CSimon * __instance;
public:

	void Update(DWORD dt);
	void Render();
	void SetState(int state);	
	static CSimon * GetInstance();
};
