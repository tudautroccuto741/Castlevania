#pragma once
#include "GameObject.h"
#include "Animations.h"

#define KNIGHT_IDLE_BBOX_WIDTH				32.0f
#define KNIGHT_IDLE_BBOX_HEIGHT				64.0f

#define KNIGHT_WALKING_SPEED				0.03f
#define KNIGHT_GRAVITY						0.001f


enum class KnightAniId
{
	walkRight = 10001,
	walkLeft = 10011
};
enum class KnightStateID
{
	stateWalkingRight = 102,
	stateWalkingLeft = 103
};

class CKnight : public CGameObject
{
	/*static CKnight * __instance;*/
public:

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) override;
	void Render() override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void ChoiceAnimation();

	CKnight();
	//~CKnight();
	//static CKnight * GetInstance();
};
