#pragma once
#include "GameObject.h"
#include "Simon.h"
#define BOSS_IDLE                   0
#define FLY_AFTER_SLEEP				1
#define ATTACK						2
#define FLY_AFTER_ATTACK			3
#define FLY_TO_THE_MIDDLE			4
#define AIM							5

#define BOSS_BBOX_WIDTH				96
#define BOSS_BBOX_HEIGHT			46

enum class BossAniID
{
	idle = 100084,
	fly = 100085
};

class CBoss : public CGameObject
{
public:
	int state;

	CBoss();
	~CBoss();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void Render() override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void ChoiceAnimations();
	void SetState(int state);
	bool isDead;
protected:
	/*CSimon* mSimon;
	int ani;*/
	DWORD timerFlyUp = 0;
	DWORD timerAim = 0;
	DWORD timerAttack = 0;
	bool isAttack;
	bool isHitSimon = false;
	bool isAtBottom;
};