#pragma once
#include "GameObject.h"
#include "Animations.h"
#define BRIDGE_BBOX_WIDTH	64
#define BRIDGE_BBOX_HEIGHT	16
#define BRIDGE_SPEED		0.05

enum class BridgeAniID
{
	idleBridge = 409
};

class CBridge : public CGameObject
{
	static CBridge * __instance;
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	float GetV() { return this->vx*this->nx; }
	CBridge();
	static CBridge * GetInstance();
};
