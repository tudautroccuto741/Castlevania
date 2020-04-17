//#include "SampleKeyHander.h"
//#include "Debug.h"
//#include "Simon.h"
//#include "Game.h"
//
////
////void CSampleKeyHander::OnKeyDown(int KeyCode)
////{
////
////	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
////	switch (KeyCode)
////	{
////	case DIK_K:
////		CSimon::GetInstance()->SetState((int)SimonStateID::stateJump);
////		break;
////	case DIK_L:
////		CSimon::GetInstance()->SetState((int)SimonStateID::stateWhip);
////		break;
////	}
////}
//
//void CSampleKeyHander::OnKeyUp(int KeyCode)
//{
//	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
//	/*switch (KeyCode)
//	{
//	case DIK_S:
//		CSimon::GetInstance()->SetState((int)SimonStateID::stateIdle);
//	}*/
//}
//
//void CSampleKeyHander::KeyState(BYTE *states)
//{
//	
//	if (CGame::GetInstance()->IsKeyDown(DIK_D))
//		CSimon::GetInstance()->SetState((int)SimonStateID::stateWalkingRight);
//	else if (CGame::GetInstance()->IsKeyDown(DIK_A))
//		CSimon::GetInstance()->SetState((int)SimonStateID::stateWalkingLeft);
//	else if (CGame::GetInstance()->IsKeyDown(DIK_S))
//		CSimon::GetInstance()->SetState((int)SimonStateID::stateSit);
//	else CSimon::GetInstance()->SetState((int)SimonStateID::stateIdle);
//}
