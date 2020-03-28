#pragma once
#include "GameObject.h"
#include "Animations.h"

#define SIMON_WALKING_SPEED		0.15f
#define SIMON_JUMP_SPEED_Y		0.4f
#define SIMON_GRAVITY			0.1f

enum class SimonAniId {

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
	IDTex = 11111,
	stateIdle = 0,

	stateWalkingRight = 100,
	stateWalkingLeft = 200,
	stateJump = 300, 
	stateSit = 400,
	stateWhip = 500
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
