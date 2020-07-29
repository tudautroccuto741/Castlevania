#pragma once
#include "GameObject.h"
#include "Game.h"
#include "DrawBoard.h"
#include "Simon.h"


#define SCORE_X			110
#define SCORE_Y			12
#define TIME_DEFAULT	300

class CBoard
{
	int _time;
	int weapon;
	DWORD _count;
	CDrawBoard* drawBoard;
	bool isStop;
	static CBoard* __instance;
	int _numberOfWeapon;
public:
	static CBoard* GetInstance();
	CBoard()
	{
		_time = TIME_DEFAULT;
		_count = GetTickCount();
		isStop = false;
		drawBoard = new CDrawBoard();
		_numberOfWeapon = 0;
		weapon = 0;
	}
	~CBoard()
	{
		if (drawBoard != NULL)
			delete drawBoard;
		drawBoard = NULL;
	}
	void Update(DWORD dt);
	void Render();
	void SetWeapon(int weapons) { weapon = weapons; }
	int GetWeapon() { return weapon; }
	int GetTime() { return _time; }
	void SetTime(int time) { this->_time = time; }
	void TimeDown() {
		if (isStop)
		{
			return;
		}
		if (GetTickCount() - _count >= 1 && _time > 0)
		{
			_time--;
			_count = GetTickCount();
			/*CSimon::GetInstance()->SetScore(10);*/

		}
	}
	void SetNumberOfWeapon(int i) { _numberOfWeapon = i; }
	int GetNumberOfWeapon() { return _numberOfWeapon; }
	void Stop() { isStop = true; }
	bool IsStop() { return isStop; }
	void ChangeWeapon();

};
