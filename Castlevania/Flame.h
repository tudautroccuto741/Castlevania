#pragma once
#include "GameObject.h"
#include "Animations.h"
#define BURNING_TIME					300
#define FLAME_BBOX_HEIGHT				30
#define FLAME_BBOX_WIDTH				16

enum class FlameAniID
{
	IDTexFlame = 500,
	idleFlame = 501
};

class CFlame : public CGameObject
{
	DWORD startBurnTime;
public:
	void Render() override;

	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void StartToBurn();

	CFlame();
};

typedef CFlame *LPFLAME;

