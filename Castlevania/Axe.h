#pragma once
#include "GameObject.h"
#define AXE_BBOX_WIDTH		30
#define AXE_BBOX_HEIGHT		28

#define AXE_FLY_SPEED_VX	0.2f
#define AXE_FLY_SPEED_VY	-0.6f
#define AXE_GRAVITY			0.0016f

#define AXE_DAMAGE			2

enum class AxeAniID
{
	FlyRight = 904,
	FlyLeft = 903
};

class CAxe : public CGameObject
{
	static CAxe * __instance;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) override;
	void Render()override;
	void SetVisible(bool visible) override;
	void ChoiceAnimations();
	CAxe();
	static CAxe * GetInstance();
};
