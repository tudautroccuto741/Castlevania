#include "Brick.h"

void CBrick::Update(DWORD dt)
{
	
}

void CBrick::Render()
{
	LPANIMATION ani;

	ani = CAnimations::GetInstance()->Get((int)BrickAniID::idlebrick);
	ani->Render(x, y);
}