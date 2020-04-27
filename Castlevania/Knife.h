#pragma once
#include "Animations.h"
#include "GameObject.h"
#include "KnifeItem.h"
#define DISTANCE_OF_KNIFE_AND_SIMON		6
#define KNIFE_FLYING_SPEED				0.3
using namespace std;

class CKnife : public CGameObject
{
	static CKnife * __instance;
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) override;
	void Render() override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void ChoiceAnimation();
	CKnife();
	static CKnife * GetInstance();
};
