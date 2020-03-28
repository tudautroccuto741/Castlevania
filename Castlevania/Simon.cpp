#include "Simon.h"

void CSimon::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	// simple fall down
	vy += SIMON_GRAVITY;	//*dt
	if (y > 100)
	{
		vy = 0; y = 100.0f;
	}

	// simple screen edge collision!!!
	if (vx > 0 && x > 230) x = 230;
	if (vx < 0 && x < 0) x = 0;
}

void CSimon::Render()
{
	int ani;

	if (vx == 0)
	{
		if (nx > 0)
		{	
			if (isJumping == true)  //jump and sit
			{ 
				ani = (int)SimonAniId::IDJumpRight;
			}
			else if (isAttacking == true) //whipping
			{
				ani = (int)SimonAniId::IDWhipRight;				
			}
			else
			{
				ani = (int)SimonAniId::idleGoRight;
			}
		}
		else 
		{
			if (isJumping == true)
			{
				ani = (int)SimonAniId::IDJumpLeft;
			}
			else if (isAttacking == true) //whipping
			{
				ani = (int)SimonAniId::IDWhipLeft;
			}
			else
			{
				ani = (int)SimonAniId::idleGoLeft;
			}
		}
	}
	else if (vx > 0)
		ani =  (int)SimonAniId::walkRight;
	else ani = (int)SimonAniId::walkLeft;

	CAnimations::GetInstance()->Get(ani)->Render(x, y);
}

void CSimon::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case (int)SimonID::stateWalkingRight:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case (int)SimonID::stateWalkingLeft:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case (int)SimonID::stateJump:
		isJumping = true;
		vy = -SIMON_JUMP_SPEED_Y;
		break;
	case (int)SimonID::stateSit:
		isJumping = true;
		break;
	case (int)SimonID::stateWhip:
		a = 0;
		while (a <= 300) 
		{
			isAttacking = true;
			a += 100;
		}
		break;
	case (int)SimonID::stateIdle:
		vx = 0;
		isJumping = false;
		isAttacking = false;
		break;
	}
}

CSimon * CSimon::__instance = NULL;
CSimon* CSimon::GetInstance()
{
	if (__instance == NULL) __instance = new CSimon();
	return __instance;
}

