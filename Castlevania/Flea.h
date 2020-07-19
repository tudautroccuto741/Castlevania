#pragma once
#include "GameObject.h"
#define FLEA_BBOX_WIDTH				32
#define FLEA_BBOX_HEIGHT			32
#define FLEA_SPEED_VX				0.04
#define FLEA_SPEED_VY				0.02
#define FLEA_DEFAULT_HEALTH			3
#define FLEA_DAMAGE					2

enum class FleaAniID
{
	flyingLeft = 100040,
	flyingRight = 100041
};

enum class FleaStateID
{
	stateFlying,
	stateTouchingSimon
};

class CFlea : public CGameObject
{
	bool isTouchSimon;
	bool isUp;
	float start_y;
public:
	
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) override;
	void Render() override;
	//void BeHit(int damage) override;
	void FindSimon();
	void SetState(int state);
	void ChoiceAnimations();
	CFlea();
};