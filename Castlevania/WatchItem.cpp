#include "WatchItem.h"


void CWatchItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy += GAME_GRAVITY * dt;				// simple fall down

	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);


	// Pick animation
	this->currentAniID = (int)WatchAniID::IDLE;


	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
	}



	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CWatchItem::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + WATCH_BBOX_WIDTH;
	bottom = y + WATCH_BBOX_HEIGHT;
}
