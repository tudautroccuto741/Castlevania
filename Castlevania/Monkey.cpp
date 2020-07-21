#include "Monkey.h"
#include "Simon.h"
#include "Brick.h"
#include "SecretBrick.h"

void CMonkey::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = MONKEY_BBOX_WIDTH + left;
	bottom = MONKEY_BBOX_HEIGHT + top;
}

void CMonkey::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	// start
	float xS, yS;
	CSimon::GetInstance()->GetPosition(xS, yS);
	if (xS < x + MONKEY_DISTANCE_WITH_SIMON && time_start == 0)
	{
		time_start = GetTickCount();
	}

	if (time_start > 0)
	{
		if (GetTickCount() - time_start >= MONKEY_TIME_START)
		{
			if(CSimon::GetInstance()->GetUntouchable() == 1)
			{
				if (isOnGround)
				{
					JumpingHigh();
				}
			}
			else
			{
				if (isOnGround)
				{
					Jumping();
					FindSimon();
				}
			}
			vy += 0.0012 * dt;
		}
		else
		{
			Start();
		}
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
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			// collision with brick

			if (dynamic_cast<CBrick *>(e->obj)
				||dynamic_cast<CSecretBrick *>(e->obj))
			{
				if (e->ny < 0)
				{
					if (isJumping)
					{
						isJumping = false;
						time_start = 0;
						
					}
					isOnGround = true;
					y += ny * 0.4f;
				}
				if (e->nx != 0)
				{
					JumpingHigh();
					FindSimon();
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (this->IsInViewport() == false&& time_start != 0)
		SetVisible(false);
}

void CMonkey::Render()
{
	ChoiceAnimations();
	CGameObject::Render();
}

void CMonkey::FindSimon()
{
	float xS, yS;
	CSimon::GetInstance()->GetPosition(xS, yS);

	if (xS > x + MONKEY_BBOX_WIDTH)
	{
		this->nx = 1;
	}
	else if (xS + SIMON_IDLE_BBOX_WIDTH < x)
	{
		this->nx = -1;
	}
}

void CMonkey::Jumping()
{
	if (!isJumping)
	{
		vy = -MONKEY_SPEED_VY;
		isJumping = true;
		dy = this->dt * vy;
		vx = MONKEY_SPEED_VX * nx;
		isOnGround = false;
	}
}

void CMonkey::JumpingHigh()
{
	if (!isJumping)
	{
		vy = -MONKEY_SPEED_VY_HIGH;
		isJumping = true;
		vx = MONKEY_SPEED_VX * nx;
		isOnGround = false;
	}
	
}

void CMonkey::Start()
{
	vy += 0.0012 * dt;
	vx = vy = 0;
	isJumping = false;
	
}

void CMonkey::SetVisible(bool visible)
{
	CGameObject::SetVisible(visible);
	
}

void CMonkey::BeHit(int damage)
{
	CGameObject::BeHit(damage);
}

void CMonkey::ChoiceAnimations()
{
	if (vx == 0 && !isOnGround)
	{
		currentAniID = (int)MonkeyAniID::start;
	}
	else if (isJumping)
	{
		currentAniID = (nx > 0) ? 
			(int)MonkeyAniID::jumpingRight:
			(int)MonkeyAniID::jumpingLeft;
	}
	else
	{
		currentAniID = (nx > 0) ? 
			(int)MonkeyAniID::idleRight:
			(int)MonkeyAniID::idleLeft;
	}
}

CMonkey::CMonkey()
{
	vx = vy = 0;
	nx = 1;
	health = MONKEY_DEFAULT_HEALTH;
	damage = MONKEY_DAMAGE;
	visible = true;
}