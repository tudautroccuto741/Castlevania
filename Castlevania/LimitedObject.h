#pragma once
#include "GameObject.h"
#include "Animations.h"
#define LIMITED_OBJECT_BBOX_WIDTH  1
#define LIMITED_OBJECT_BBOX_HEIGHT 64

class CLimitedObject: public CGameObject
{

public:
	virtual void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	CLimitedObject();
};

