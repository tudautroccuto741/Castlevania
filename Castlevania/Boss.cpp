#include "Boss.h"
#include "Game.h"

void CBoss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (CSimon::GetInstance()->GetFreezing())
		return;

	CGameObject::Update(dt);

	x += dx;
	y += dy;

	SetState(state);

	float xS, yS;
	CSimon::GetInstance()->GetPosition(xS, yS);
	if (xS > x + BOSS_BBOX_WIDTH && health > 0 && state == 0)
	{
		state = FLY_AFTER_SLEEP;
	}
	
	//else
	//{
	//	SetState()
	//}

	float l, t, r, b;
	CGame::GetInstance()->CamereBoundingBox(l, t, r, b);

	if (state != 0)
	{
		if (x <= l)
			vx = -vx;
		if (x >= r)
			vx = -vx;
		if (y <= t)
			vy = 0.03f;
	}
	
}

void CBoss::ChoiceAnimations()
{
	if (vx != 0
		|| vy!=0)
	{
		currentAniID = (int)BossAniID::fly;
	}
	else
	{
		currentAniID = (int)BossAniID::idle;
	}
}

void CBoss::SetState(int state)
{
	float xS, yS;
	CSimon::GetInstance()->GetPosition(xS, yS);
	switch (state)
	{
	case FLY_AFTER_SLEEP:
		if (y <= 90)
		{
			vy = 0.03f;
		}
		else
		{
			vx = 0;
			vy = 0;
			state = ATTACK;
			this->state = state;
		}
		break;
	case ATTACK:  //attack
		if (timerAttack < 3000)
		{
			timerAttack += dt;
		}
		else
		{
			timerAttack = 0;
			isAttack = true;
		}
		if ((abs(x - xS) >= 70 && isHitSimon == false) || isAttack == true)
		{
			if (xS < x)
			{
				vx = -0.08f;
				vy = 0.078f;
				isHitSimon = true;
			}
			else
			{
				vx = 0.08f;
				vy = 0.078f;
				isHitSimon = true;
			}
			isAttack = false;
		}
		if (abs(y - yS) <= 5) 
		{
			vy = 0;
			if (abs(xS - x) >= 5)
			{
				vy = -0.038f;
				state = FLY_AFTER_ATTACK;
				this->state = state;
			}
		}
		if (y - yS >= 60) 
		{
			vy = -0.038f;
			state = FLY_AFTER_ATTACK;
			this->state = state;
		}
		break;
	case FLY_AFTER_ATTACK: 
		if (timerFlyUp < 1200)
			timerFlyUp += dt;
		else
		{
			timerFlyUp = 0;
			state = FLY_TO_THE_MIDDLE;
			this->state = state;
		}
		break;

	case FLY_TO_THE_MIDDLE:
		if (x != 640) 
		{
			if (x < 635)
			{
				vx = 0.07f;
				vy = -0.01f;
			}
			else
			{
				vx = -0.07f;
				vy = -0.01f;
			}
		}
		if (x >= 620 && x < 650)
		{
			vx = 0;
			vy = 0;
			state = AIM;
			this->state = state;
		}
		break;

	case AIM:
		if (this->y <= 100)
			vy = 0.02f;
		else
			vy = 0;

		if (abs(x - xS)> 60)
		{
			if (xS < x)
				vx = -0.055f;
		}
		else
		{
			vx = 0;
		}

		isHitSimon = false;
		if (timerAim < 2000)
		{
			timerAim += dt;
		}
		else
		{
			state = ATTACK;
			this->state = state;
			timerAim = 0;
		}
		break;
	}
}

void CBoss::Render()
{
	if (CSimon::GetInstance()->freezing)
	{
		animations->GetInstance()->Get(currentAniID)->RenderbyFrame(animations->Get(currentAniID)->GetCurrentFrame(), x, y, alpha);
	}
	else
	{
		ChoiceAnimations();
		CGameObject::Render();
	}
}

void CBoss::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = BOSS_BBOX_WIDTH + left;
	bottom = BOSS_BBOX_HEIGHT + top;
}

CBoss::CBoss()
{
	state = 0;
	CGameObject::SetVisible(true);
	vx = vy = 0;
	currentAniID = (int)BossAniID::idle;
	health = 16;
	isAttack = false;
	isHitSimon = false;
	isAtBottom = false;
}