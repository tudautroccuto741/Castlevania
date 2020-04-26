#pragma once
#include "Animations.h"
#include "GameObject.h"
#include "KnifeItem.h"
using namespace std;

class CKnife : public CGameObject
{
	
	static CKnife * __instance;
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) override;
	void Render() override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void SetVisible(bool visible) override;
	bool IsOverlapping(LPGAMEOBJECT obj) override;
	void ChoiceAnimation();
	void UpdatePosition();
	CKnife();
	static CKnife * GetInstance();
};
