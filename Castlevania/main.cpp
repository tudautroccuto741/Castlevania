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
#include "Flame.h"

#define WINDOW_CLASS_NAME L"Castlevania"
#define MAIN_WINDOW_TITLE L"Castlevania"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(200, 200, 255)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define MAX_FRAME_RATE 60
#define ID_TEX_MISC 20

CGame *game;
CSampleKeyHander * keyHandler;
LPGAMEOBJECT gameObject;

vector<LPGAMEOBJECT> defaultObjects;


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
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	LPANIMATION ani;

	textures->Add((int)SimonStateID::IDTex, L"textures\\1.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texsimon = textures->Get((int)SimonStateID::IDTex);

	// readline => id, left, top, right, bottom

	// Simon action
	// idle simon go right
	sprites->Add(10001, 436, 2, 468, 64, texsimon);
	sprites->Add(10002, 374, 2, 406, 64, texsimon);
	sprites->Add(10003, 313, 2, 345, 64, texsimon);
	sprites->Add(10004, 256, 2, 288, 64, texsimon);

	ani = new CAnimation(100);
	ani->Add(10001);
	animations->Add((int)SimonAniId::idleGoRight, ani);

	ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	ani->Add(10004);
	animations->Add((int)SimonAniId::walkRight, ani);

	//idle simon go left
	sprites->Add(10011, 12, 200, 44, 262, texsimon);
	sprites->Add(10012, 74, 200, 106, 262, texsimon);
	sprites->Add(10013, 135, 200, 167, 262, texsimon);
	sprites->Add(10014, 192, 200, 224, 262, texsimon);

	ani = new CAnimation(100);
	ani->Add(10011);
	animations->Add((int)SimonAniId::idleGoLeft, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	ani->Add(10014);
	animations->Add((int)SimonAniId::walkLeft, ani);

	//simon sit right
	sprites->Add(10020, 196, 18, 228, 64, texsimon);

	ani = new CAnimation(100);
	ani->Add(10020);
	animations->Add((int)SimonAniId::IDSitRight, ani);

	//simon sit left
	sprites->Add(10021, 252, 216, 284, 262, texsimon);

	ani = new CAnimation(100);
	ani->Add(10021);
	animations->Add((int)SimonAniId::IDSitLeft, ani);

	//simon sit and whipping right
	sprites->Add(10022, 16, 67, 48, 113, texsimon);
	sprites->Add(10023, 437, 133, 469, 179, texsimon);
	sprites->Add(10024, 375, 133, 407, 179, texsimon);

	ani = new CAnimation(150);
	ani->Add(10022);
	ani->Add(10023);
	ani->Add(10024);
	animations->Add((int)SimonAniId::IDSitAndWhippingRight, ani);

	//simon sit and whipping left
	sprites->Add(10025, 432, 265, 464, 311, texsimon);
	sprites->Add(10026, 11, 331, 43, 377, texsimon);
	sprites->Add(10027, 73, 331, 105, 377, texsimon);

	ani = new CAnimation(150);
	ani->Add(10025);
	ani->Add(10026);
	ani->Add(10027);
	animations->Add((int)SimonAniId::IDSitAndWhippingLeft, ani);

	//simon whipping right
	sprites->Add(10031, 136, 2, 168, 64, texsimon);
	sprites->Add(10032, 75, 2, 107, 64, texsimon);
	sprites->Add(10033, 16, 2, 48, 64, texsimon);

	ani = new CAnimation(150);
	ani->Add(10031);
	ani->Add(10032);
	ani->Add(10033);
	animations->Add((int)SimonAniId::IDWhippingRight, ani);

	//simon whipping left
	sprites->Add(10035, 312, 200, 344, 262, texsimon);
	sprites->Add(10036, 373, 200, 405, 262, texsimon);
	sprites->Add(10037, 432, 200, 464, 262, texsimon);

	ani = new CAnimation(150);
	ani->Add(10035);
	ani->Add(10036);
	ani->Add(10037);
	animations->Add((int)SimonAniId::IDWhippingLeft, ani);

	CSimon::GetInstance()->SetPosition(50.0f, 0);

	//brick
	textures->Add((int)BrickAniID::IDTexBrick, L"textures\\3.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texbrick = textures->Get((int)BrickAniID::IDTexBrick);

	/*sprites->Add(30000, 129, 67, 161, 99, texbrick);
	CBrick *brick = new CBrick();
	ani = new CAnimation(100);
	ani->Add(30000);
	animations->Add((int)BrickAniID::idleBrick, ani);
	defaultObjects.push_back(brick);
	brick->SetPosition(0, 168);*/

	for (int i = 0; i < 30; i++)
	{
		CBrick *brick = new CBrick();
		animations->Add((int)BrickAniID::idleBrick, ani);
		brick->SetPosition(0 + i * 32.0f, 150);
		defaultObjects.push_back(brick);
	}

	sprites->Add(30000, 129, 67, 161, 99, texbrick);
	CBrick *brick = new CBrick();
	ani = new CAnimation(100);
	ani->Add(30000);
	animations->Add((int)BrickAniID::idleBrick, ani);
	defaultObjects.push_back(brick);
	brick->SetPosition(0, 168);

	// candle
	textures->Add((int)CandleAniID::IDTexCandle, L"textures\\3.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texCandle = textures->Get((int)CandleAniID::IDTexCandle);

	sprites->Add(40001, 0, 0, 32, 64, texCandle);
	sprites->Add(40002, 32, 0, 64, 64, texCandle);

	ani = new CAnimation(100);
	ani->Add(40001);
	ani->Add(40002);

	animations->Add((int)CandleAniID::idleCandle, ani);
	gameObject = new CCandle();
	gameObject->SetPosition(200.0f, 86);
	defaultObjects.push_back(gameObject);


	// Flame
	textures->Add((int)FlameAniID::idleFlame, L"textures\\3.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texFlame = textures->Get((int)FlameAniID::IDTexFlame);

	sprites->Add(50001, 67, 42, 83, 62, texFlame);
	sprites->Add(50002, 113, 7, 129, 37, texFlame);
	sprites->Add(50003, 156, 7, 172, 37, texFlame);
	sprites->Add(50004, 198, 7, 214, 37, texFlame);

	ani = new CAnimation(100);
	ani->Add(50001);
	ani->Add(50002);
	ani->Add(50003);
	ani->Add(50004);
	animations->Add((int)FlameAniID::idleFlame, ani);


	// whipping
	textures->Add((int)WhipAniID::IDTexWhip, L"textures\\2.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texweapon = textures->Get((int)WhipAniID::IDTexWhip);

	//weapon: Whipping right
	sprites->Add(10040, 420, 2, 452, 64, texweapon);
	sprites->Add(10041, 358, 2, 390, 64, texweapon);
	sprites->Add(10042, 262, 2, 318, 36, texweapon);

	ani = new CAnimation(150);
	ani->Add(10040);
	ani->Add(10041);
	ani->Add(10042);
	animations->Add((int)WhipAniID::idleWhippingRight, ani);

	//weapon: Whipping left
	sprites->Add(10043, 2, 2, 34, 64, texweapon);
	sprites->Add(10044, 63, 2, 95, 64, texweapon);
	sprites->Add(10045, 135, 4, 191, 38, texweapon);

	ani = new CAnimation(150);
	ani->Add(10043);
	ani->Add(10044);
	ani->Add(10045);
	animations->Add((int)WhipAniID::idleWhippingLeft, ani);

	// sprite - sprite - sprite 
// (---100---)(---100---)(---100---)

	gameObject = CSimon::GetInstance();
	defaultObjects.push_back(gameObject);


	//defaultObjects.push_back(candle);

	gameObject = CWhip::GetInstance();
	defaultObjects.push_back(gameObject);

}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < defaultObjects.size(); i++)
	{
		coObjects.push_back(defaultObjects[i]);
	}

	for (int i = 0; i < defaultObjects.size(); i++)
	{
		defaultObjects[i]->Update(dt, &coObjects);
	}

	float cx, cy;
	CSimon::GetInstance()->GetPosition(cx, cy);

	cx -= SCREEN_WIDTH / 4;
	cy -= SCREEN_HEIGHT / 4;

	CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
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


		for (int i = 0; i < defaultObjects.size(); i++)
			if (defaultObjects[i]->GetVisible())
				defaultObjects[i]->Render();

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

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}