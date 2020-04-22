#pragma once
#include "Weapons.h"
#include "Animations.h"
#include "GameObject.h"

#define FRONT_WHIP_BBOX_WIDTH_LV1	56.0f
#define FRONT_WHIP_BBOX_HEIGHT_LV1	34.0f
#define FRONT_WHIP_BBOX_WIDTH_LV2	56.0f
#define FRONT_WHIP_BBOX_HEIGHT_LV2	34.0f
#define FRONT_WHIP_BBOX_WIDTH_LV3	89.0f
#define FRONT_WHIP_BBOX_HEIGHT_LV3	34.0f

#define BACK_WHIP_BBOX_WIDTH		32
#define BACK_WHIP_BBOX_HEIGHT		62

#define WHIP_LV1					20001
#define WHIP_LV2					20004
#define WHIP_LV3					20007

using namespace std;

enum class WhipAniID
{
	idleWhippingRight = 9994,
	idleWhippingLeft = 9995,
	idleWhippingRightLv2 = 9996,
	idleWhippingLeftLv2 = 9997,
	idleWhippingRightLv3 = 9998,
	idleWhippingLeftLv3 = 9999
};

class CWhip : public CGameObject
{
	int lv;
	static CWhip * __instance;
	
public:

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) override;
	void Render() override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void SetVisible(bool visible) override;
	bool IsOverlapping(LPGAMEOBJECT obj) override;
	void UpdatePosition(int aniID);
	void ChoiceAnimation();
	void LvUp();
	CWhip();
	static CWhip * GetInstance();

};

