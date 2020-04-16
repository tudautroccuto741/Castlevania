#include "Brick.h"

/*void CBrick::Update(DWORD dt)
{
	//x = x + x*dt + 32;
}*/

void CBrick::Render()
{
	LPANIMATION ani;
	ani = CAnimations::GetInstance()->Get((int)BrickAniID::idleBrick);
	for (int i = 0; i < 30; i++)
	{
		ani->Render(x + i * 32, y);
	}

}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}
CBrick::CBrick()
{
	visible = true;
}