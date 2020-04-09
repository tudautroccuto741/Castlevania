#pragma once
#include "Weapons.h"
#include "Animations.h"
#include "GameObject.h"
#define FRONT_WHIP_BBOX_WIDTH	56.0f
#define FRONT_WHIP_BBOX_HEIGHT	34.0f
#define BACK_WHIP_BBOX_WIDTH	32
#define BACK_WHIP_BBOX_HEIGHT	62



using namespace std;

enum class WhipAniID
{
	IDTexWhip,
	idleWhippingRight = 9999,
	idleWhippingLeft = 9998
};

class CWhip : public CGameObject
{
	static CWhip * __instance;
	
public:

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) override;
	void Render() override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void SetVisible(bool visible) override;

	void UpdatePosition(int aniID);

	static CWhip * GetInstance();

};

