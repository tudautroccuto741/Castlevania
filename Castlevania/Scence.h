#pragma once

#include <d3dx9.h>
#include "KeyEventHandler.h"
#include "Cells.h"

class CScene
{
protected:
	CKeyEventHandler * key_handler;
	int id;
	LPCWSTR sceneFilePath;

public:
	int mapWidth = 0;
	int mapHeight = 0;
	int GetMapWidth() { return this->mapWidth; }
	int GetMapHeight() { return this->mapHeight; }
	void GetTileMapReSize(int &mapwidth, int &mapheight) { mapwidth = mapWidth; mapheight = mapHeight; }
	CCells * cells;
	CCells * GetCells() { return this->cells; }
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> visibleObjects;
	vector<LPGAMEOBJECT> defaultObjects;
	//the object need be updated
	vector<LPGAMEOBJECT> updateObjects;
	void GetGameObjects(vector<LPGAMEOBJECT> * &object)
	{
		object = &this->visibleObjects;
	}

	CScene(int id, LPCWSTR filePath);

	CKeyEventHandler * GetKeyEventHandler() { return key_handler; }
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
};
typedef CScene * LPSCENE;


class CScenceKeyHandler : public CKeyEventHandler
{
protected:
	CScene * scence;

public:
	virtual void KeyState(BYTE *states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	CScenceKeyHandler(CScene *s) :CKeyEventHandler() { scence = s; }
};