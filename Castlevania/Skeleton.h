#pragma once
#include "GameObject.h"
#define SKELETON_BBOX_WIDTH				32
#define SKELETON_BBOX_HEIGHT			64
#define SKELETON_SPEED_VX				0.15f
#define SKELETON_SPEED_VY				0.4f
#define SKELETON_DEFAULT_HEALTH			1
#define SKELETON_DAMAGE					2
#define SKELETON_DISTANCE_TO_VISIBLE	160


enum class SkeletonAniID
{
	WalkLeft = 100072,
	WalkRight = 100070
};

enum class SkeletonStateID
{
	stateWalking,
	stateJump
};

class CSkeleton : public CGameObject
{
	bool isRender;
	bool isJumping;
	bool isChangeLimited;
	int nxM;
	float limitedLeft, limitedRight;
public:

	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) override;
	void Render() override;
	void SetVisible(bool visible) override;
	void ChangeDirection();
	void Walking();
	void Jump();
	bool ChekDistanceWithSimon();
	void ChangeLimited();
	void ChoiceAnimations();
	CSkeleton();
};