#pragma once
#include "GameObject.h"
#define AQUAFINA_IDLE_BBOX_HEIGHT			16
#define AQUAFINA_IDLE_BBOX_WIDTH			16
#define AQUAFINA_BOOM_BBOX_HEIGHT			26
#define AQUAFINA_BOOM_BBOX_WIDTH			32

#define AQUAFINA_IDLE_GRAVITY				0.0007f
#define AQUAFINA_IDLE_FLY_SPEED_VX			0.15f
#define AQUAFINA_IDLE_FLY_SPEED_VY			-0.08f

#define AQUAFINA_BOOM_TIME					800
#define AQUAFINA_DAMAGE						2

enum class AquafinaAniID
{
	right = 905,
	left = 906,
	boom = 907
};

class CAquafina : public CGameObject
{
	bool boom = false;
	DWORD boom_start = 0;
	static CAquafina * __instance;

public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) override;
	void Render()override;
	void SetVisible(bool visible) override;
	void ChoiceAnimations();

	CAquafina();
	static CAquafina * GetInstance();

};
