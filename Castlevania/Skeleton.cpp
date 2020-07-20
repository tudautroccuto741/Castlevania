#include "Skeleton.h"
#include "Simon.h"
#include "Brick.h"

void CSkeleton::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = SKELETON_BBOX_WIDTH + x;
	bottom = SKELETON_BBOX_HEIGHT + y;
}

void CSkeleton::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	vy += 0.001 * dt;

	ChangeDirection();
	if (isRender)
	{
		/*if (x <= 64)
		{
			limitedLeft = 64;
			nxM = 1;
		}*/
		/*else
		{*/
			if (!isJumping && isChangeLimited)
			{
				ChangeLimited();
			}
			Walking();
		/*}*/

	}
		
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
		float l, t, r, b;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			// collision with brick

			if (dynamic_cast<CBrick *>(e->obj))
			{
				e->obj->GetBoundingBox(l, t, r, b);
				if (e->ny < 0)
				{
					if (x < l || x + SKELETON_BBOX_WIDTH > r)
					{
						Jump();
					}
					else
					{
						isJumping = false;
						vy = 0;
						Walking();
						y += ny * 0.4f;
						
					}
				}
				if (e->nx > 0)
				{
					x += nx * 0.4f;
					float xB, yB;
					e->obj->GetPosition(xB, yB);
					isChangeLimited = false;
					limitedLeft = xB+32;
				}
				else
				{
					isChangeLimited = true;
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (this->IsInViewport() == false)
		health = 0;
	if (!visible)
	{
		isRender = false;
	}
}

void CSkeleton::ChangeDirection()
{
	float xS, yS;
	CSimon::GetInstance()->GetPosition(xS, yS);

	if (xS > x + SKELETON_BBOX_WIDTH)
	{
		this->nx = 1;
	}
	else if (xS + SIMON_IDLE_BBOX_WIDTH < x)
	{
		this->nx = -1;
	}
}

void CSkeleton::Walking()
{
	limitedRight = limitedLeft + 32;
	if(x >= limitedRight)
	{
		nxM = -1;
	}
	else if (x <= limitedLeft)
	{
		nxM = 1;
	}	
	vx = nxM * SKELETON_SPEED_VX;
}

void CSkeleton::Jump()
{
	if (!isJumping)
	{
		isJumping = true;
		vy = -SKELETON_SPEED_VY;
		vx = nxM * SKELETON_SPEED_VX;
		limitedLeft = limitedRight = 0;
	}
}

bool CSkeleton::ChekDistanceWithSimon()
{
	float xS, yS;
	CSimon::GetInstance()->GetPosition(xS, yS);

	if (abs(x - xS) < SKELETON_DISTANCE_TO_VISIBLE)
	{
		return true;
	}

	if (nx == 1)
		if (abs(x - xS) - SKELETON_BBOX_WIDTH < SKELETON_DISTANCE_TO_VISIBLE)
		{
			return true;
		}

	return false;
}

void CSkeleton::ChangeLimited()
{
	float xS, yS;
	CSimon::GetInstance()->GetPosition(xS, yS);
	if (ChekDistanceWithSimon()/*&&!isJumping*/)
	{
		if (nx > 0)
		{
			limitedLeft = xS - 160;
		}
		else
		{
			limitedLeft = xS + 160;
		}

	}
}


void CSkeleton::ChoiceAnimations()
{
	if (nx > 0)
	{
		currentAniID = (int)SkeletonAniID::WalkRight;
	}
	else
	{
		currentAniID = (int)SkeletonAniID::WalkLeft;
	}
}

void CSkeleton::SetVisible(bool visible)
{
	CGameObject::SetVisible(visible);
}

void CSkeleton::Render()
{
	if (ChekDistanceWithSimon() || vx != 0)
	{
		isRender = true;
		ChoiceAnimations();
		CGameObject::Render();
	}
}

CSkeleton::CSkeleton()
{
	nxM = 1;
	vx = 0;
	vy = 0;
	health = SKELETON_DEFAULT_HEALTH;
	damage = SKELETON_DAMAGE;
	visible = true;
	isRender = false;
	isJumping = false;
	isChangeLimited = true;
}