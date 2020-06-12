#include "Door.h"
void CDoor::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + DOOR_BBOX_WIDTH;
	b = y + DOOR_BBOX_HEIGHT;
}
CDoor::CDoor()
{
	visible = true;
	currentAniID = (int)DoorAniID::idle;
}