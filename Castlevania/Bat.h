#pragma once
#include "GameObject.h"
#define BAT_BBOX_WIDTH				32
#define BAT_BBOX_HEIGHT				32
#define BAT_SPEED_VX				0.07
#define BAT_SPEED_VY				0.05
#define BAT_DEFAULT_HEALTH			1
#define BAT_DAMAGE					2
#define DISTANCE_WITH_SIMON_X		224
#define DISTANCE_WITH_SIMON_Y		80
#define DISTANCE_BAT_FLYING_HORIZONTAL	79

enum class BatAniID
{
	idle = 10002,
	flyingRight = 100021
};
enum class BatStateID
{
	stateidle,
	stateflyingRight
};

class CBat : public CGameObject
{
	float start_y;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) override;
	void Render() override;
	void SetState(int state);
	void ChoiceAnimations();
	CBat();
};

