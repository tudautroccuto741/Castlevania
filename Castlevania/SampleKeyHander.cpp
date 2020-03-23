#include "SampleKeyHander.h"
#include "Debug.h"
#include "Simon.h"
#include "Game.h"


void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
		CSimon::GetInstance()->SetState(SIMON_STATE_JUMP);
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	if (CGame::GetInstance()->IsKeyDown(DIK_RIGHT))
		CSimon::GetInstance()->SetState(SIMON_STATE_WALKING_RIGHT);
	else if (CGame::GetInstance()->IsKeyDown(DIK_LEFT))
		CSimon::GetInstance()->SetState(SIMON_STATE_WALKING_LEFT);
	else CSimon::GetInstance()->SetState(SIMON_STATE_IDLE);
}
