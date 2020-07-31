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
		state = (int)BossStateID::flyAfterSleepp;
	}
	

	float l, t, r, b;
	CGame::GetInstance()->CamereBoundingBox(l, t, r, b);

	if (state != 0)
	{
		if (x <= l)
			vx = -vx;
		if (x+BOSS_BBOX_WIDTH >= r)
			vx = -vx;
		if (y <= t)
			vy = 0.03f;
	}
	
}

void CBoss::ChoiceAnimations()
{
	if (state != (int)BossStateID::idle)
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
	case (int)BossStateID::flyAfterSleepp:
		if (y <= 180)
		{
			vy = 0.03f;
		}
		else
		{
			vx = 0;
			vy = 0;
			state = (int)BossStateID::attack;
			this->state = state;
		}
		break;
	case (int)BossStateID::attack:
		if (timerAttack < 3000)
		{
			timerAttack += dt;
		}
		else
		{
			timerAttack = 0;
			isAttack = true;
		}
		if ((abs(x - xS) >= 140 && isHitSimon == false) || isAttack == true)
		{
			if (xS < x)
			{
				vx = -0.16f;
				vy = 0.078f;
				isHitSimon = true;
			}
			else
			{
				vx = 0.16f;
				vy = 0.078f;
				isHitSimon = true;
			}
			isAttack = false;
		}
		if (abs(y - yS) <= 10)
		{
			vy = 0;
			if (abs(xS - x) >= 10)
			{
				vy = -0.038f;
				state = (int)BossStateID::flyAfterAttack;
				this->state = state;
			}
		}
		if (y - yS >= 120)
		{
			vy = -0.038f;
			state = (int)BossStateID::flyAfterAttack;
			this->state = state;
		}
		break;
	case (int)BossStateID::flyAfterAttack:
		if (timerFlyUp < 2400)
			timerFlyUp += dt;
		else
		{
			timerFlyUp = 0;
			state = (int)BossStateID::flyToTheMiddle;
			this->state = state;
		}
		break;
	case (int)BossStateID::flyToTheMiddle:
		if (x != 1280) 
		{
			if (x < 1270)
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
		if (x >= 1240 && x < 1300)
		{
			vx = 0;
			vy = 0;
			state = (int)BossStateID::aim;
			this->state = state;
		}
		break;

	case (int)BossStateID::aim:
		if (this->y <= 200)
			vy = 0.02f;
		else
			vy = 0;

		if (abs(x - xS)> 120)
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
			state = (int)BossStateID::attack;
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
	state = (int)BossStateID::idle;
	CGameObject::SetVisible(true);
	vx = vy = 0;
	currentAniID = (int)BossAniID::idle;
	health = 16;
	isAttack = false;
	isHitSimon = false;
	isAtBottom = false;
}