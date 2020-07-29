#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Simon.h"
#include "Tile.h"
#include "Board.h"
#include "Flea.h"
#include "Raven.h"
#include "Skeleton.h"
#include "Monkey.h"

class CPlayScene : public CScene //dai dien 1 canh choi
{
protected:
	CSimon *player;				// A play scene has to have player, right? 
	int tileMapLineY = 0;
	int tileMapWidth = 0;
	int tileMapHeight = 0;
	int limitedSmallMapLeft = 0;
	int limitedSmallMapRight = 0;

	//LPSCENE _stage;
	//int mapWidth = 0;
	//int mapHeight = 0;

	vector<LPTILE> tileMap;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_TILE_MAP_INFOR(string line);
	void _ParseSection_TILE_MAP(string line);
public:

	CPlayScene(int id, LPCWSTR filePath);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	
	void GetVisibleObjects()
	{
		LPGAMEOBJECT object;
		for (size_t i = 0; i < objects.size(); i++)
		{
			object = this->objects[i];
			if (dynamic_cast<CSimon *>(object)
				//|| dynamic_cast<CWhip *>(object)
				/*|| dynamic_cast<CFlea *>(object)
				|| dynamic_cast<CRaven *>(object)
				|| dynamic_cast<CSkeleton *>(object)
				|| dynamic_cast<CMonkey *>(object)*/
				/*|| dynamic_cast<CKnife *>(object)
				|| dynamic_cast<CBoomerang *>(object)
				|| dynamic_cast<CAquafina *>(object)
				|| dynamic_cast<CAxe *>(object)*/
				|| object->GetVisible() == false)
			{
				defaultObjects.push_back(object);
			}
			else
			{
				visibleObjects.push_back(object);
			}
		}
	}
	friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

