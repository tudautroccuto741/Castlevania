#pragma once
#include "GameObject.h"
#include "Animations.h"

#define SIMON_WALKING_SPEED		0.15f
#define SIMON_JUMP_SPEED_Y		0.4f
#define SIMON_GRAVITY			0.1f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300


#define SIMON_ANI_IDLE_RIGHT		0
#define SIMON_ANI_IDLE_LEFT			1
#define SIMON_ANI_WALKING_RIGHT		2
#define SIMON_ANI_WALKING_LEFT		3
#define SIMON_ANI_JUMP_RIGHT		4
#define SIMON_ANI_JUMP_LEFT			5

enum class SimonAniId {
	IDLEGORIGHT = 400,
	IDLEGOLEFT = 401,
	WALKRIGHT = 500,
	WALKLEFT = 501,
	IDJUMPRIGHT = 600,
	IDJUMPLEFT = 601,
	ID_TEX_SIMON = 0
};

class CSimon : public CGameObject
{

	float x = 0;
	float y = 0;

	float vx = 0;
	float vy = 0;

	int nx = 1;
	bool isJumping;
	bool isState;

	static CSimon * __instance;
public:

	void Update(DWORD dt);
	void Render();
	void SetState(int state);	
	void Jump();
	static CSimon * GetInstance();
};
