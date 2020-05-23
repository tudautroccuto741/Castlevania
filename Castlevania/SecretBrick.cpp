#include "SecretBrick.h"

void CSecretBrick::Render()
{

}

void CSecretBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + SECRET_BRICK_BBOX_WIDTH;
	b = y + SECRET_BRICK_BBOX_HEIGHT;
}

CSecretBrick::CSecretBrick()
{
	this->currentAniID = (int)SecretBrickAniID::idle;
	visible = true;
}