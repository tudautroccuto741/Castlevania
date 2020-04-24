#include "Brick.h"

void CBrick::Render()
{

}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}
CBrick::CBrick()
{
	visible = true;
}