#pragma once
#include "GameObject.h"
#define STAIRS_UP_BBOX_WIDTH	32
#define STAIRS_UP_BBOX_HEIGHT	32

class CStairsUp : public CGameObject
{
public:
	void GetBoundingBox(float &l, float &t, float &r, float &b)override;
	void Render() override { ; }
	CStairsUp();
};

