/* =============================================================

================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Sprites.h"
#include "Animations.h"
#include "Simon.h"
#include "Brick.h"
#include "Candle.h"
#include "SampleKeyHander.h"

#define WINDOW_CLASS_NAME L"Castlevania"
#define MAIN_WINDOW_TITLE L"Castlevania"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(200, 200, 255)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define MAX_FRAME_RATE 60
#define ID_TEX_MISC 20

CGame *game;
//CSimon *simon;

//CBrick * brick;
//CCandle * candle;
CSampleKeyHander * keyHandler;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources
	In this example: load textures, sprites, animations and SIMON object
*/
void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();

	textures->Add((int)SimonAniId::ID_TEX_SIMON, L"textures\\1.png", D3DCOLOR_XRGB(255, 0, 255));
	//textures->Add(ID_TEX_BRICK, L"textures\\3.png", D3DCOLOR_XRGB(255, 0, 255));
	//textures->Add((int)CandleAniID::ID_TEX_CANDLE, L"textures\\3.png", D3DCOLOR_XRGB(255, 0, 255));


	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texsimon = textures->Get((int)SimonAniId::ID_TEX_SIMON);

	// readline => id, left, top, right, bottom
	sprites->Add(10001, 240, 0, 300, 66, texsimon);		//idle simon go right
	sprites->Add(10002, 310, 0, 350, 66, texsimon);
	sprites->Add(10003, 420, 0, 480, 66, texsimon);
	sprites->Add(10004, 540, 0, 600, 66, texsimon);

	sprites->Add(10011, 180, 198, 240, 264, texsimon);	//idle simon go left
	sprites->Add(10012, 120, 198, 180, 264, texsimon);
	sprites->Add(10013, 60, 198, 120, 264, texsimon);
	sprites->Add(10014, 0, 198, 60, 264, texsimon);

	/*LPDIRECT3DTEXTURE9 texBrick = textures->Get((int)BrickAniID::ID_TEX_BRICK); //brick
	sprites->Add(20001, 127, 65, 162, 100, texMisc);	*/

	//LPDIRECT3DTEXTURE9 texCandle = textures->Get((int)CandleAniID::ID_TEX_CANDLE); //candle
	//sprites->Add(30001, 0, 0, 32, 64, texCandle);


	LPANIMATION ani;

	ani = new CAnimation(100);
	ani->Add(10001);
	animations->Add((int)SimonAniId::IDLEGOLEFT, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	animations->Add((int)SimonAniId::IDLEGORIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	ani->Add(10004);
	animations->Add((int)SimonAniId::WALKRIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	ani->Add(10014);
	animations->Add((int)SimonAniId::WALKLEFT, ani);




	CSimon::GetInstance()->AddAnimation((int)SimonAniId::IDLEGOLEFT);
	CSimon::GetInstance()->AddAnimation((int)SimonAniId::IDLEGORIGHT);
	CSimon::GetInstance()->AddAnimation((int)SimonAniId::WALKRIGHT);
	CSimon::GetInstance()->AddAnimation((int)SimonAniId::WALKLEFT);

	CSimon::GetInstance()->SetPosition(0.0f, 100.0f);
	/*simon = new CSimon();
	simon->AddAnimation((int)SimonAniId::IDLEGOLEFT);
	simon->AddAnimation((int)SimonAniId::IDLEGORIGHT);

	simon->SetPosition(0.0f, 100.0f);*/

/*	ani = new CAnimation(100);
	ani->Add(20001);

	animations->Add((int)BrickAniID::STAND, ani);
	

	
	brick = new CBrick();
	brick->AddAnimation((int)BrickAniID::STAND);

	brick->SetPosition(10.0f, 100.0f);
	*/
	/*ani = new CAnimation(100);
	ani->Add(30001);
	
	animations->Add((int)CandleAniID::STAND, ani);

	candle = new CCandle();
	candle->AddAnimation((int)CandleAniID::STAND);

	candle->SetPosition(20.0f, 50.0f);*/

}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	CSimon::GetInstance()->Update(dt);
//	brick->Update(dt);
	//candle->Update(dt);
}


/*
	Render a frame
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		CSimon::GetInstance()->Render();
//		brick->Render();
		//candle->Render();

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();

			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);

	LoadResources();
	Run();

	return 0;
}