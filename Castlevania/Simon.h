#pragma once
#include "GameObject.h"
#include "Animations.h"

#define SIMON_WALKING_SPEED		0.1f
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_GRAVITY			0.1f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300

#define SIMON_ANI_IDLE_RIGHT		0
#define SIMON_ANI_IDLE_LEFT			1
#define SIMON_ANI_WALKING_RIGHT		2
#define SIMON_ANI_WALKING_LEFT		3

enum class SimonAniId {
	IDLEGORIGHT = 500,
	IDLEGOLEFT = 501,
	ID_TEX_SIMON = 0
};

class CSimon : public CGameObject
{

	float x =0;
	float y =0;

	float vx =0;
	float vy =0;

	int nx = 1;
	static CSimon * __instance;
public:

	void Update(DWORD dt);
	void Render();
	void SetState(int state);	
	static CSimon * GetInstance();
};
