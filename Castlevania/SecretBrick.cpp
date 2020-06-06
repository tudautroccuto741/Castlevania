#include "SecretBrick.h"
#include "Rocks.h"
#include "Items.h"

DWORD CSecretBrick::cannot_be_hit_start = 0;

void CSecretBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + SECRET_BRICK_BBOX_WIDTH;
	b = y + SECRET_BRICK_BBOX_HEIGHT;
}

void CSecretBrick::Destroy()
{
	CRocks::GetInstance()->ShowSomeRocksAfterBreaking(this->x, this->y);
	CItems::GetInstance()->CheckAndDrop(this);
	this->SetVisible(false);
}

void CSecretBrick::BeHit(int damage)
{
	if (GetTickCount() - cannot_be_hit_start > CANNOT_BE_HIT_TIME)
		cannot_be_hit_start = 0;

	if (cannot_be_hit_start == 0)
	{
		CGameObject::BeHit(damage);
		cannot_be_hit_start = GetTickCount();
	}
}

CSecretBrick::CSecretBrick()
{
	this->currentAniID = (int)SecretBrickAniID::idle;
	visible = true;
} 