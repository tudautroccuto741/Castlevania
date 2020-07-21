#include "Watch.h"


void CWatch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy += GAME_GRAVITY * dt;				// simple fall down

	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);



	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
	}
	else


	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];


	// If the item watch goes out the viewport
	if (this->IsInViewport() == false)
		SetVisible(false);
}

void CWatch::Render()
{
	// Pick animation
	this->currentAniID = (int)WatchAniID::IDLE;

	CGameObject::Render();
}

void CWatch::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + WATCH_BBOX_WIDTH;
	bottom = y + WATCH_BBOX_HEIGHT;
}
