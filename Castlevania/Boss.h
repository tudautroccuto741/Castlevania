#pragma once
#include "GameObject.h"
#include "Simon.h"

#define BOSS_BBOX_WIDTH				96
#define BOSS_BBOX_HEIGHT			46

enum class BossAniID
{
	idle = 100084,
	fly = 100085
};

enum class BossStateID
{
	idle,
	flyAfterSleepp,
	attack,
	flyAfterAttack,
	flyToTheMiddle,
	aim
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

	DWORD timerFlyUp = 0;
	DWORD timerAim = 0;
	DWORD timerAttack = 0;
	bool isAttack;
	bool isHitSimon = false;
	bool isAtBottom;
};