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
				ani = (int)SimonAniId::aniJumpRight;
			}
			else if (isAttacking == true) //whipping
			{
				ani = (int)SimonAniId::aniWhipRight;				
			}
			else
			{
				ani = (int)SimonAniId::aniIdleRight;
			}
		}
		else 
		{
			if (isJumping == true)
			{
				ani = (int)SimonAniId::aniJumpLeft;
			}
			else if (isAttacking == true) //whipping
			{
				ani = (int)SimonAniId::aniWhipLeft;
			}
			else
			{
				ani = (int)SimonAniId::aniIdleLeft;
			}
		}
	}
	else if (vx > 0)
		ani =  (int)SimonAniId::aniWalkingRight;
	else ani = (int)SimonAniId::aniWalkingLeft;

	animations[ani]->Render(x, y);
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

