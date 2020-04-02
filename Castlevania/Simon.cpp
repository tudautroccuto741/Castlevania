#include "Simon.h"


void CSimon::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	// Calculate dx, dy 
	//CGameObject::Update(dt);

	// check attack state
	if (isAttacking && GetTickCount() - start > 450)
	{
		whip->Update(dt);
		isAttacking = false;
	}

	

	//else
	//{
		//whip->GetInstance()->Update(dt);
	//}

	// simple fall down
	vy += SIMON_GRAVITY * dt;
	if (y > 100)
	{
		vy = 0; y = 100.0f;
	}

	if (vx > 0 && x > 290) x = 290;
	if (vx < 0 && x < 0) x = 0;


	/*vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	// turn off collision when die 
	if (currentState != MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
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

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable == 0)
					{
						if (goomba->GetState() != GOOMBA_STATE_DIE)
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								level = MARIO_LEVEL_SMALL;
								StartUntouchable();
							}
							else
								SetState(MARIO_STATE_DIE);
						}
					}
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	*/
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
				whip->Render();
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
				whip->Render();
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
	if (isAttacking) {
		return;
	}

	CGameObject::SetState(state);
	switch (state)
	{
	case (int)SimonStateID::stateWalkingRight:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case (int)SimonStateID::stateWalkingLeft:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case (int)SimonStateID::stateJump:
		isJumping = true;
		vy = -SIMON_JUMP_SPEED_Y;
		break;
	case (int)SimonStateID::stateSit:
		isJumping = true;
		break;
	case (int)SimonStateID::stateWhip:
		isAttacking = true;
		start = GetTickCount();
		isUsingweapon = true;
		break;
	case (int)SimonStateID::stateIdle:
		vx = 0;
		isJumping = false;
		isAttacking = false;
		break;
	}
}

/*void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;

	if (level == MARIO_LEVEL_BIG)
	{
		right = x + MARIO_BIG_BBOX_WIDTH;
		bottom = y + MARIO_BIG_BBOX_HEIGHT;
	}
	else
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}
}*/


CSimon * CSimon::__instance = NULL;
CSimon* CSimon::GetInstance()
{
	if (__instance == NULL) __instance = new CSimon();
	return __instance;
}

CSimon::CSimon() : x(0), y (0), vx (0), vy(0), nx(1)
{
	whip = new CWhip();
}

CSimon::~CSimon()
{
	delete whip;
}