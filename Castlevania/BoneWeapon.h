#pragma once
#include"GameObject.h"

#define BONE_BBOX_WIDTH		32
#define BONE_BBOX_HEIGHT	32

#define BONE_SPEED_VX		0.14
#define BONE_SPEED_VY		0.6

enum BoneWeaponAniID
{
	FLYING_LEFT = 100077,
	FLYING_RIGHT = 100074
};

class CBoneWeapon : public CGameObject
{

public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) override;
	void SetVisible(bool visible) override;
	void Render() override;
	CBoneWeapon();
};
typedef CBoneWeapon * LPBONE;
