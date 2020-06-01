#include "LimitedObject.h"
void CLimitedObject::Render()
{
	;
}

void CLimitedObject::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + LIMITED_OBJECT_BBOX_WIDTH;
	b = y + LIMITED_OBJECT_BBOX_HEIGHT;
}

CLimitedObject::CLimitedObject()
{
	visible = true;
}