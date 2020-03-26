#include "SampleKeyHander.h"
#include "Debug.h"
#include "Simon.h"
#include "Game.h"


void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_UP:
		CSimon::GetInstance()->SetState((int)SimonID::stateJump);
		break;
	/*case DIK_X:
		CSimon::GetInstance()->SetState((int)SimonID::stateWhip);*/
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	switch (KeyCode)
	{
	/*case DIK_UP:
		CSimon::GetInstance()->SetState((int)SimonID::stateJump);
		break;*/
	case DIK_X:
		CSimon::GetInstance()->SetState((int)SimonID::stateWhip);
	}
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	if (CGame::GetInstance()->IsKeyDown(DIK_RIGHT))
		CSimon::GetInstance()->SetState((int)SimonID::stateWalkingRight);
	else if (CGame::GetInstance()->IsKeyDown(DIK_LEFT))
		CSimon::GetInstance()->SetState((int)SimonID::stateWalkingLeft);
	else if (CGame::GetInstance()->IsKeyDown(DIK_Z))
		CSimon::GetInstance()->SetState((int)SimonID::stateSit);
	else CSimon::GetInstance()->SetState((int)SimonID::stateIdle);
}
