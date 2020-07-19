#pragma once
#include "GameObject.h"
#define MONKEY_BBOX_WIDTH				32
#define MONKEY_BBOX_HEIGHT				32
#define MONKEY_SPEED_VX					0.25f
#define MONKEY_SPEED_VY_HIGH			0.4f
#define MONKEY_SPEED_VY					0.12f
#define MONKEY_DISTANCE_WITH_SIMON		238
#define MONKEY_TIME_START				500
#define MONKEY_DEFAULT_HEALTH			1
#define MONKEY_DAMAGE					2

enum class MonkeyAniID
{
	start = 100050,
	idleRight = 100052,
	idleLeft = 100053,
	jumpingRight = 100054,
	jumpingLeft = 100055
};

enum class MonkeyStateID
{
	stateStart,
	stateIdle,
	stateJump,
	stateJumpHigh,
	stateTouchingSimon
};

class CMonkey : public CGameObject
{
	bool isTouchSimon;
	bool isUp;
	bool isJumping;
	bool isOnGround;
	DWORD time_start;
public:

	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) override;
	void Render() override;
	void BeHit(int damage) override;
	void SetVisible(bool visible) override;
	void FindSimon();
	void Start();
	void Jumping();
	void JumpingHigh();
	void ChoiceAnimations();
	CMonkey();
};