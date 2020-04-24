#pragma once
#include "Animations.h"
#include "GameObject.h"
#include "Knife.h"
using namespace std;

class CWeaponKnife : public CGameObject
{
	
	static CWeaponKnife * __instance;
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) override;
	void Render() override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void SetVisible(bool visible) override;
	bool IsOverlapping(LPGAMEOBJECT obj) override;
	void ChoiceAnimation();
	void Attack();
	CWeaponKnife();
	static CWeaponKnife * GetInstance();
};
