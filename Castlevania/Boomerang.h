#pragma once
#include "Animations.h"
#include "GameObject.h"
#include "KnifeItem.h"
#define BOOMERANG_BBOX_WIDTH				28
#define BOOMERANG_BBOX_HEIGHT				28
#define DISTANCE_OF_BOOMERANG_AND_SIMON		0
#define BOOMERANG_FLYING_SPEED				0.2
#define BOOMERANG_DISTANCE_WITH_SIMOM		200
using namespace std;

enum class BoomerangAniID
{
	BoomerangRight = 901,
	BoomerangLeft = 902
};

class CBoomerang : public CGameObject
{
	int isReturn;
	float xS, yS;
	static CBoomerang * __instance;
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) override;
	void Render() override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void SetVisible(bool visible) override;
	void ChoiceAnimation();
	CBoomerang();
	static CBoomerang * GetInstance();
};