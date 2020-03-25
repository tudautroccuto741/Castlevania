#include "Simon.h"

void CSimon::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	// simple fall down
	vy += SIMON_GRAVITY;
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
			if (isJumping == true) 
			{ 
				ani = SIMON_ANI_JUMP_RIGHT; 
			}
			else 
			{ 
				ani = SIMON_ANI_IDLE_RIGHT; 
			}
		}
		else 
		{
			if (isJumping == true)
			{
				ani = SIMON_ANI_JUMP_LEFT;
			}
			else ani = SIMON_ANI_IDLE_LEFT;
		}
	}
	else if (vx > 0)
		ani = SIMON_ANI_WALKING_RIGHT;
	else ani = SIMON_ANI_WALKING_LEFT;

	animations[ani]->Render(x, y);
}

void CSimon::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMP:
		isJumping = true;
		vy = -SIMON_JUMP_SPEED_Y;
		break;
	case SIMON_STATE_IDLE:
		vx = 0;
		isJumping = false;
		break;
	}
}

CSimon * CSimon::__instance = NULL;
CSimon* CSimon::GetInstance()
{
	if (__instance == NULL) __instance = new CSimon();
	return __instance;
}

void CSimon::Jump()
{
	if (!isJumping)
	{
		isJumping = true;
		//this->vy = -SIMON_JUMP_SPEED_Y;
	}
}