#include "WhipItem.h"

void CWhipItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy += GAME_GRAVITY * dt;				// simple fall down

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);


	float min_tx, min_ty, nx = 0, ny;
	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
	}
	else
	{
		// block 
		//x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CWhipItem::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + WHIP_ITEM_BBOX_WIDTH;
	bottom = y + WHIP_ITEM_BBOX_HEIGHT;
}

CWhipItem::CWhipItem()
{
	// Pick animation
	this->currentAniID = (int)WhipItemAniID::idleWhipItem;
	visible = false;
}