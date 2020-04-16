#include "PlaySceneKeyHandler.h"
#include "Simon.h"
#include "PlayScene.h"
#include "SceneKeyHandler.h"

void CPlaySceneKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CSimon *simon = ((CPlayScene*)scene)->player;
	switch (KeyCode)
	{
	case DIK_SPACE:
		simon->SetState((int)SimonStateID::stateJump);
		break;
	/*case DIK_A: // reset
		simon->SetState(SIMON_STATE_IDLE);
		simon->SetLevel(SIMON_LEVEL_BIG);
		simon->SetPosition(50.0f, 0.0f);
		simon->SetSpeed(0, 0);
		break;
	}*/
}

//void CPlaySceneKeyHandler::OnKeyUp(int KeyCode)
//{}

void CPlaySceneKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	CSimon *simon = ((CPlayScene*)scence)->player;

	// disable control key when simon die 
	if (simon->GetState() == SIMON_STATE_DIE) return;
	if (game->IsKeyDown(DIK_RIGHT))
		simon->SetState(SIMON_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		simon->SetState(SIMON_STATE_WALKING_LEFT);
	else
		simon->SetState(SIMON_STATE_IDLE);
}