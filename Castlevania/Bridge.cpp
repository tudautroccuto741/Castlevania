#include "Bridge.h"
#include"Brick.h"

void CBridge::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	x += dx;
	if (x < 65)
	{
		SetDirection(1);
	}
	if (x > 128)
	{
		SetDirection(-1);
	}
	vx = (nx > 0) ? BRIDGE_SPEED : -BRIDGE_SPEED;
}

void CBridge::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRIDGE_BBOX_WIDTH;
	b = y + BRIDGE_BBOX_HEIGHT;
}

CBridge::CBridge()
{
	this->currentAniID = (int)BridgeAniID::idleBridge;
	visible = true;
}