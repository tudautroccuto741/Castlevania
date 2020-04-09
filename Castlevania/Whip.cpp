#include "Whip.h"
#include "GameObject.h"
#include "Simon.h"
#include "Candle.h"

CWhip * CWhip::__instance = NULL;

void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (visible)
	{
		CGameObject::Update(dt);

		int nnx = CSimon::GetInstance()->GetDirection();
		currentAniID = (nnx > 0) ? ((int)WhipAniID::idleWhippingRight) : ((int)WhipAniID::idleWhippingLeft);
		UpdatePosition(currentAniID);
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
	/*if(animations->Get(currentAniID)->GetCurrentFrame()==2)
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CCandle *>(e->obj)) // if e->obj is candle 
			{
				CCandle *candle = dynamic_cast<CCandle *>(e->obj);

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
		}*/
	for (UINT i = 0; i < coEvents.size(); i++)
	{
		delete coEvents[i];
		// empty now
	}
}

void CWhip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	float xS, yS;
	CSimon::GetInstance()->GetPosition(xS, yS);

	left = x;
	top = y;

	// whip front.
	if ((nx > 0 && x > xS) || (nx < 0 && x < xS))
	{
		right = x + FRONT_WHIP_BBOX_WIDTH;
		bottom = y + FRONT_WHIP_BBOX_HEIGHT;
	}
	
}


void CWhip::UpdatePosition(int aniID)
{
	float xS, yS;
	CSimon::GetInstance()->GetPosition(xS, yS);
	
	float whipTexWidth = FRONT_WHIP_BBOX_WIDTH;

	LPANIMATION ani = CAnimations::GetInstance()->Get(aniID);
	int nxw = CSimon::GetInstance()->GetDirection();

	if (ani->GetCurrentFrame() == 2)
	{
		x = (nxw > 0) ? 
			xS + SIMON_IDLE_BBOX_WIDTH :
			xS - whipTexWidth;
	}
	else
	{
		x = (nxw > 0) ? 
			xS - BACK_WHIP_BBOX_WIDTH : 
			xS + SIMON_IDLE_BBOX_WIDTH;
	}
	y = yS;
}

void CWhip::Render()
{
	CGameObject::Render();
	
}

void CWhip::SetVisible(bool visible)
{ 
	CGameObject::SetVisible(visible);
	if (this->visible)
		if (currentAniID > 0)
			this->ResetAnimationTimer(currentAniID);
}



CWhip * CWhip::GetInstance()
{
	if (__instance == NULL)__instance = new CWhip();

	return __instance;
}
