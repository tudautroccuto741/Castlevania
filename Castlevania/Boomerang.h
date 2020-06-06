#pragma once
#include "Animations.h"
#include "GameObject.h"
#include "KnifeItem.h"
#define BOOMERANG_BBOX_WIDTH				28
#define BOOMERANG_BBOX_HEIGHT				28
#define DISTANCE_OF_BOOMERANG_AND_SIMON		0
#define BOOMERANG_FLYING_SPEED				0.2
#define BOOMERANG_FLYING_TIME				2000
using namespace std;

enum class BoomerangAniID
{
	BoomerangRight = 901,
	BoomerangLeft = 902
};

class CBoomerang : public CGameObject
{
	bool isReturn;
	static CBoomerang * __instance;
	DWORD start_time_turn_around;
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) override;
	void Render() override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void ChoiceAnimation();
	CBoomerang();
	static CBoomerang * GetInstance();
};