#include "Crown.h"
#include "Simon.h"

void CCrown::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + CROWN_BBOX_WIDTH;
	bottom = y + CROWN_BBOX_HEIGHT;
}

void CCrown::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	// grow up
	float xS, yS;
	CSimon::GetInstance()->GetPosition(xS, yS);
	if (xS >= DISTANCE_SIMON_GROW_UP_X && yS <= DISTANCE_SIMON_GROW_UP_Y)
	{
		currentAniID = (int)CrownAniID::GROWUP;
		vy = -CROWN_GROWING_UP_SPEED;
	}
	if (y <= LIMITED_GROW_UP_Y)
	{
		y = LIMITED_GROW_UP_Y;
		vy = 0;
	}
	// growing up in this place
	/*if (y <= LIMITED_GROW_UP_Y)
	{
		y = LIMITED_GROW_UP_Y;
		vy = 0;
	}
	else
	{
		if (xS >= DISTANCE_SIMON_GROW_UP_X && yS<= DISTANCE_SIMON_GROW_UP_Y)
		{
			currentAniID = (int)CrownAniID::GROWUP;
			vy = -CROWN_GROWING_UP_SPEED;
		}
	}*/

	// Update position
	x += dx;
	y += dy;

}

CCrown::CCrown()
{
	visible = true;
	currentAniID = (int)CrownAniID::IDLE;
	vx = vy = 0;
}