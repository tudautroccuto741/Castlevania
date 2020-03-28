#pragma once
#include"AnimationFrame.h"
#include<vector>

using namespace std;

class CAnimation
{
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(int defaultTime);
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y);
};

typedef CAnimation *LPANIMATION;