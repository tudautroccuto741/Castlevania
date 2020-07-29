#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "Sprite.h"
#include "Sprites.h"
#include"AnimationFrame.h"

using namespace std;

class CAnimation
{
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;

public:
	CAnimation();
	CAnimation(int defaultTime);

	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y, int alpha = 255);

	int GetCurrentFrame() { return currentFrame; };
	void SetCurrentFrame(int index) { this->currentFrame = index; }
	void RenderbyFrame(int currentFrame, float x, float y, int alpha);
	void ResetFrameStartTime();
};

typedef CAnimation *LPANIMATION;