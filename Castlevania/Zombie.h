#pragma once
#include "GameObject.h"
#include "Animations.h"

#define ZOMBIE_IDLE_BBOX_WIDTH				32.0f
#define ZOMBIE_IDLE_BBOX_HEIGHT				64.0f

#define ZOMBIE_WALKING_SPEED				0.1f	
#define ZOMBIE_GRAVITY						0.001f
#define ZOMBIE_HEALTH						1


enum class ZombieAniId
{
	walkRight = 100080,
	walkLeft = 100082
};


class CZombie : public CGameObject
{
public:

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) override;
	void Render() override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void ChoiceAnimation();
	void BeHit(int damage) override;

	CZombie();
};
