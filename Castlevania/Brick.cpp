#include "Brick.h"

void CBrick::Update(DWORD dt)
{
	
}

void CBrick::Render()
{
	LPANIMATION ani;
	//if (vx > 0) ani = animations[0]; else ani = animations[1];
	ani = animations[3];
	ani->Render(x, y);
}