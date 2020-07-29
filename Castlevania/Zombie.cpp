#include "Zombie.h"
#include "Brick.h"
#include "Simon.h"

void CZombie::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
 	if (CSimon::GetInstance()->GetFreezing())
		return;
	CGameObject::Update(dt);

	vy += ZOMBIE_GRAVITY * dt;
	vx = (nx > 0) ? ZOMBIE_WALKING_SPEED : -ZOMBIE_WALKING_SPEED;

	// untouchable
	if (start_untouchable != 0)
	{
		Untouchable();
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);
	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		x += min_tx * dx;
		y += min_ty * dy;


		// collision logic with other objects
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			// collision with brick

			if (dynamic_cast<CBrick *>(e->obj))
			{
				if (e->ny != 0)
				{
					y += ny * 0.4f;
					vy = 0;
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	/*if (this->IsInViewport() == false)
		SetVisible(false);*/
}

void CZombie::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + ZOMBIE_IDLE_BBOX_WIDTH;
	bottom = y + ZOMBIE_IDLE_BBOX_HEIGHT;
}

void CZombie::ChoiceAnimation()
{
	if (vx != 0)
	{
		currentAniID = (nx > 0) ?
			(int)ZombieAniId::walkRight :
			(int)ZombieAniId::walkLeft;
	}
}

void CZombie::Render()
{
	if (CSimon::GetInstance()->freezing)
	{
		animations->GetInstance()->Get(currentAniID)->RenderbyFrame(animations->Get(currentAniID)->GetCurrentFrame(), x, y, alpha);
	}
	else
	{
		ChoiceAnimation();
		CGameObject::Render();
	}

}

void CZombie::BeHit(int damage)
{
	CGameObject::BeHit(damage);
}

CZombie::CZombie()
{
	this->currentAniID = (int)ZombieAniId::walkRight;
	visible = true;
	health = ZOMBIE_HEALTH;
	nx = -1;
}
