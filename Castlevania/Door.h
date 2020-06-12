#pragma once
#include "GameObject.h"
#include "Animations.h"
#define DOOR_BBOX_WIDTH  16
#define DOOR_BBOX_HEIGHT 96
enum class DoorAniID
{
	idle = 124
};
class CDoor : public CGameObject
{
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	CDoor();
};
