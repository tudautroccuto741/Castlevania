#include "Simon.h"

void CSimon::Update(DWORD dt)
{
	x += vx * dt;
	if ((vx > 0 && x > 290) || (x < 0 && vx < 0)) vx = -vx;
}

void CSimon::Render()
{
	LPANIMATION ani;

	if (vx > 0) ani = CAnimations::GetInstance()->Get(500); 
	else ani = CAnimations::GetInstance()->Get(501);
	//ani = animations[0];
	ani->Render(x, y);
}