#include "Raven.h"
#include "Simon.h"
#include "CameraChangeViewObject.h"

void CRaven::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = RAVEN_BBOX_WIDTH + left;
	bottom = RAVEN_BBOX_HEIGHT + top;
}

void CRaven::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	//start 
	float xC, yC;
	CCameraChangeViewObject::GetInstance()->GetPosition(xC, yC);
	float xS, yS;
	CSimon::GetInstance()->GetPosition(xS, yS);
	if (xS > x - RAVEN_DISTANCE_WITH_SIMON && time_start == 0 && yS < yC)
	{
		time_start = GetTickCount();
	}

	ChangeDirection();

	if (time_start > 0)
	{
		if (GetTickCount() - time_start >= RAVEN_TIME_START)
		{
			if (ny > 0) 
			{
				if (y > yTemp + RAVEN_DISTANCE_TO_FLY)
				{
					Stop();
					CheckDistanceWithSimon();
				}
				else
				{
					if (!isTouchingSimon)
					{
						FlyingToAttack();
					}
				}
			}
			else
			{
				if (y + RAVEN_DISTANCE_TO_FLY < yTemp )
				{
					Stop();
					CheckDistanceWithSimon();
				}
				else
				{
					if (!isTouchingSimon)
					{
						FlyingToAttack();
					}
				}
			}
			
		}
		else
		{
			Start();
		}
	}

	if (time_to_stop != 0)
	{
		if (GetTickCount() - time_to_stop >= RAVEN_TIME_PAUSE)
		{
			if (!isTouchingSimon)
			{
				FlyingToAttack();
			}
			time_to_stop = 0;
		}
		else
		{
			Stop();
			CheckDistanceWithSimon();
		}
	}
	
	//attack
	if (isTouchingSimon || CSimon::GetInstance()->GetUntouchable() == 1)
	{
		Attack();
		isTouchingSimon = false;
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
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (this->IsInViewport() == false && time_start != 0)
		SetVisible(false);
}

void CRaven::Render()
{
	ChoiceAnimations();
	CGameObject::Render();
}

void CRaven::ChangeDirection()
{
	float xS, yS;
	CSimon::GetInstance()->GetPosition(xS, yS);

	if (xS > x + RAVEN_BBOX_WIDTH)
	{
		this->nx = 1;
	}
	else if (xS + SIMON_IDLE_BBOX_WIDTH < x)
	{
		this->nx = -1;
	}

	if (y < yS)
	{
		ny = 1;
	}
	else
	{
		ny = -1;
	}
}

void CRaven::FlyingToAttack()
{
	vx = nx * RAVEN_SPEED_VX;
	vy = ny * RAVEN_SPEED_VY;
}

void CRaven::Attack()
{
	vx = this->lastnx * RAVEN_SPEED_VX;
	isStop = false;
	time_to_stop = 0;
}

void CRaven::CheckDistanceWithSimon()
{
	float xS, yS;
	CSimon::GetInstance()->GetPosition(xS, yS);
	if ((y + RAVEN_BBOX_HEIGHT >= yS)&&(x <= xS + SIMON_IDLE_BBOX_WIDTH))
	{
		isTouchingSimon = true;
	}
	else
	{
		isTouchingSimon = false;
	}
	if (isStop)
	{
		this->lastnx = GetDirection();
	}
}

void CRaven::Stop()
{
	if (!isStop)
	{
		isStop = true;
		time_to_stop = GetTickCount();
		vx = vy = 0;
	}
}

void CRaven::Start()
{
	vx = vy = 0;
	isStop = false;
	GetPosition(x, yTemp);
}

void CRaven::SetVisible(bool visible)
{
	CGameObject::SetVisible(visible);
}

void CRaven::BeHit(int damage)
{
	CGameObject::BeHit(damage);
}

void CRaven::ChoiceAnimations()
{
	if (vx != 0 || isStop)
	{
		currentAniID = (nx > 0) ? 
			(int)RavenAniID::flyRight: 
			(int)RavenAniID::flyLeft;
	}
	else
	{
		currentAniID = (int)RavenAniID::idle;
	}
}

CRaven::CRaven()
{
	vx = vy = 0;
	nx = -1;
	health = RAVEN_DEFAULT_HEALTH;
	damage = RAVEN_DAMAGE;
	visible = true;
	isStop = false;
	time_start = 0;
}