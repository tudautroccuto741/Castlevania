#include "Candle.h"

void CCandle::Update(DWORD dt)
{

}

void CCandle::Render()
{
	LPANIMATION ani;

	ani = CAnimations::GetInstance()->Get((int)CandleAniID::STAND);
	ani->Render(x, y);
}