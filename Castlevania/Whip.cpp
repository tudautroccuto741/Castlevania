#include "Whip.h"
#include "Simon.h"

void CWhip::Update(DWORD dt)
{
	int nx = CSimon::GetInstance()->GetDirection();
	float a = CSimon::GetInstance()->GetX();
	float b = CSimon::GetInstance()->GetY();
	time = CSimon::GetInstance()->GetTimeStar();
	if (nx > 0) 
	{
		if (GetTickCount() - time > 150 && GetTickCount() - time < 300)
		{
			x = a - 44;
			isUsingweapon = false;
		}
		else if (GetTickCount() - time > 300 && GetTickCount() - time < 450)
		{
			x = a - 45;
			isUsingweapon = false;
		}
		else if(GetTickCount() - time > 450)
		{
			x = a + 48;
			isUsingweapon = false;
		}
	}
	else 
	{
		if (GetTickCount() - time > 150 && GetTickCount() - time < 300)
		{
			x = a + 44;
			isUsingweapon = false;
		}
		else if (GetTickCount() - time > 300 && GetTickCount() - time < 450)
		{
			x = a + 45;
			isUsingweapon = false;
		}
		else if (GetTickCount() - time > 450)
		{
			x = a - 48;
			isUsingweapon = false;
		}
	}
	y = b;
}

void CWhip::Render()
{
	int nx = CSimon::GetInstance()->GetDirection();
	LPANIMATION ani;

	if (nx > 0)
	{
		ani = CAnimations::GetInstance()->Get((int)WhipAniID::idleWhipRight);
	}
	else
	{
		ani = CAnimations::GetInstance()->Get((int)WhipAniID::idleWhipLeft);
	}
	ani->Render(x, y);
}
