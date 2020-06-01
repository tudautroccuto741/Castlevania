#pragma once
#include "GameObject.h"
#include "Animations.h"

#define CAMERA_CHANGE_VIEW_BBOX_WIDTH  32
#define CAMERA_CHANGE_VIEW_BBOX_HEIGHT 62

enum class CameraChangeViewObjectAniID
{
	idle = 4011
};
class CCameraChangeViewObject : public CGameObject
{
	static CCameraChangeViewObject * __instance;

public:
	virtual void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	float GetX() { return this->x; }
	float GetY() { return this->y; }
	CCameraChangeViewObject();
	static CCameraChangeViewObject * GetInstance();
};
