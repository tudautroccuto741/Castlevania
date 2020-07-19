#pragma once
#include "GameObject.h"
#define RAVEN_BBOX_WIDTH				32
#define RAVEN_BBOX_HEIGHT				32
#define RAVEN_SPEED_VX					0.15f
#define RAVEN_SPEED_VY_HIGH				0.2f
#define RAVEN_SPEED_VY					0.12f
#define RAVEN_DISTANCE_WITH_SIMON		224
#define RAVEN_DISTANCE_TO_FLY			80
#define RAVEN_TIME_START				600
#define RAVEN_TIME_PAUSE				1000
#define RAVEN_DEFAULT_HEALTH			1
#define RAVEN_DAMAGE					3


enum class RavenAniID
{
	idle = 100060,
	flyLeft = 100061,
	flyRight = 100064,
};

enum class RavenStateID
{
	stateStart,
	stateIdle,
	stateJump,
	stateJumpHigh,
	stateTouchingSimon
};

class CRaven : public CGameObject
{
	DWORD time_to_stop;
	DWORD time_start;
	float yTemp, xTemp;
	int lastnx;
	bool isStop;
	bool isTouchingSimon;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) override;
	void Render() override;
	void BeHit(int damage) override;
	void ChangeDirection();
	void FlyingToAttack();
	void Attack();
	void Start();
	void Stop();
	void CheckDistanceWithSimon();
	void SetVisible(bool visible) override;
	void ChoiceAnimations();
	CRaven();
};