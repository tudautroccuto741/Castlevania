#pragma once
#include "GameObject.h"
#define STAIRS_DOWN_BBOX_WIDTH	32
#define STAIRS_DOWN_BBOX_HEIGHT	64

class CStairsDown : public CGameObject
{
public:
	void GetBoundingBox(float &l, float &t, float &r, float &b)override;
	void Render() override { RenderBoundingBox(); }
	CStairsDown();
};

