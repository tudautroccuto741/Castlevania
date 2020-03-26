#pragma once
#include "GameObject.h"
#include "Animations.h"

#define SIMON_WALKING_SPEED		0.15f
#define SIMON_JUMP_SPEED_Y		0.4f
#define SIMON_GRAVITY			0.1f

enum class SimonAniId {
	idleGoRight = 400,
	idleGoLeft = 401,
	walkRight = 500,
	walkLeft = 501,
	IDJumpRight = 600,
	IDJumpLeft = 601,
	IDWhipRight = 700,
	IDWhipLeft = 701,


	aniIdleRight =	0,
	aniIdleLeft = 1,
	aniWalkingRight = 2,
	aniWalkingLeft	= 3,
	aniJumpRight =	4,
	aniJumpLeft = 5,
	aniWhipRight = 6,
	aniWhipLeft = 7
};
enum class SimonID
{
	IDTex = 0,
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
	bool isWhipping;

	static CSimon * __instance;
public:

	void Update(DWORD dt);
	void Render();
	void SetState(int state);	
	static CSimon * GetInstance();
};
