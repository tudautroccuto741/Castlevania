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
#include "Whip.h"

#define WINDOW_CLASS_NAME L"Castlevania"
#define MAIN_WINDOW_TITLE L"Castlevania"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(200, 200, 255)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define MAX_FRAME_RATE 60
#define ID_TEX_MISC 20

CGame *game;
CWhip *weapon;
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

	textures->Add((int)SimonStateID::IDTex, L"textures\\1.png", D3DCOLOR_XRGB(255, 0, 255));
	//textures->Add(ID_TEX_BRICK, L"textures\\3.png", D3DCOLOR_XRGB(255, 0, 255));
	//textures->Add((int)CandleAniID::ID_TEX_CANDLE, L"textures\\3.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add((int)WhipAniID::IDTexWhip, L"textures\\2.png", D3DCOLOR_XRGB(255, 0, 255));


	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texsimon = textures->Get((int)SimonStateID::IDTex);
	LPDIRECT3DTEXTURE9 texweapon = textures->Get((int)WhipAniID::IDTexWhip);

	// readline => id, left, top, right, bottom
	sprites->Add(10001, 420, 0, 480, 66, texsimon);		//idle simon go right
	sprites->Add(10002, 240, 0, 300, 66, texsimon);		
	sprites->Add(10003, 300, 0, 360, 66, texsimon);
	sprites->Add(10004, 360, 0, 420, 66, texsimon);


	sprites->Add(10011, 0, 198, 60, 264, texsimon);		//idle simon go left
	sprites->Add(10012, 180, 198, 240, 264, texsimon);	
	sprites->Add(10013, 120, 198, 180, 264, texsimon);
	sprites->Add(10014, 60, 198, 120, 264, texsimon);

	sprites->Add(10020, 180, 0, 240, 66, texsimon);		//simon sit right
	sprites->Add(10021, 240, 198, 300, 264, texsimon);		//simon sit left

		//simon whipping right
	sprites->Add(10031, 119, 0, 179, 66, texsimon);
	sprites->Add(10032, 59, 0, 119, 66, texsimon);
	sprites->Add(10033, 0, 0, 60, 66, texsimon);

		//simon whipping left
	sprites->Add(10035, 300, 198, 360, 264, texsimon);
	sprites->Add(10036, 360, 198, 420, 264, texsimon);
	sprites->Add(10037, 420, 198, 480, 264, texsimon);

	//weapon: Whip
	sprites->Add(10040, 392, 0, 452, 66, texweapon);
	sprites->Add(10041, 330, 0, 390, 66, texweapon);
	sprites->Add(10042, 262, 0, 322, 66, texweapon);

	sprites->Add(10043, 2, 0, 62, 66, texweapon);
	sprites->Add(10044, 63, 0, 123, 66, texweapon);
	sprites->Add(10045, 131, 0, 191, 66, texweapon);



	/*LPDIRECT3DTEXTURE9 texBrick = textures->Get((int)BrickAniID::ID_TEX_BRICK); //brick
	sprites->Add(20001, 127, 65, 162, 100, texMisc);	*/

	//LPDIRECT3DTEXTURE9 texCandle = textures->Get((int)CandleAniID::ID_TEX_CANDLE); //candle
	//sprites->Add(30001, 0, 0, 32, 64, texCandle);


	LPANIMATION ani;

	ani = new CAnimation(100);
	ani->Add(10001);
	animations->Add((int)SimonAniId::idleGoRight, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	animations->Add((int)SimonAniId::idleGoLeft, ani);

	ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	ani->Add(10004);
	animations->Add((int)SimonAniId::walkRight, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	ani->Add(10014);
	animations->Add((int)SimonAniId::walkLeft, ani);

	ani = new CAnimation(100);
	ani->Add(10020);
	animations->Add((int)SimonAniId::IDJumpRight, ani);

	ani = new CAnimation(100);
	ani->Add(10021);
	animations->Add((int)SimonAniId::IDJumpLeft, ani);

	// sprite - sprite - sprite 
// (---100---)(---100---)(---100---)
	ani = new CAnimation(150);
	ani->Add(10031); 
	ani->Add(10032);
	ani->Add(10033);
	animations->Add((int)SimonAniId::IDWhipRight, ani);

	ani = new CAnimation(150);
	ani->Add(10035);
	ani->Add(10036);
	ani->Add(10037);
	animations->Add((int)SimonAniId::IDWhipLeft, ani);	


	CSimon::GetInstance()->SetPosition(0.0f, 100.0f);
	
	ani = new CAnimation(150);
	ani->Add(10040);
	ani->Add(10041);
	ani->Add(10042);
	animations->Add((int)WhipAniID::idleWhipRight, ani);

	ani = new CAnimation(150);
	ani->Add(10043);
	ani->Add(10044);
	ani->Add(10045);
	animations->Add((int)WhipAniID::idleWhipLeft, ani);

	//CWhip::GetInstance()->SetPosition(0.0f, 100.f);

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