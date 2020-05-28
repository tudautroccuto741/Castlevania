#include <iostream>
#include <fstream>
#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Debug.h"
#include "Candle.h"
#include "Tile.h"
#include "Flame.h"
#include "Flames.h"
#include "Items.h"
#include "WhipItem.h"
#include "HeartItem.h"
#include "Knife.h"
#include "KnifeItem.h"
#include "Weapons.h"
#include "Knight.h"
#include "StairsUp.h"
#include "StairsDown.h"
#include "SmallCandle.h"
#include "BoomerangItem.h"
#include "Boomerang.h"
#include "Bridge.h"
#include "SecretBrick.h"
#include "SmallHeart.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN			-1
#define SCENE_SECTION_TEXTURES			2
#define SCENE_SECTION_SPRITES			3
#define SCENE_SECTION_ANIMATIONS		4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS			6
#define SCENE_SECTION_TILEMAP			7


#define OBJECT_TYPE_SIMON				0
#define OBJECT_TYPE_WHIP				1
#define OBJECT_TYPE_CANDLE				2
#define OBJECT_TYPE_SMALL_CANDLE		21
#define OBJECT_TYPE_BRICK				3
#define OBJECT_TYPE_SECRET_BRICK		411
#define OBJECT_TYPE_STAIRS_UP			31
#define OBJECT_TYPE_STAIRS_DOWN			32
#define OBJECT_TYPE_BRIDGE				39
#define OBJECT_TYPE_FLAMES				4
#define OBJECT_TYPE_HEART				6
#define OBJECT_TYPE_SMALL_HEART			61
#define OBJECT_TYPE_WHIPITEM			7
#define OBJECT_TYPE_KNIFE_ITEM			8
#define OBJECT_TYPE_KNIFE				9
#define OBJECT_TYPE_BOOMERANG_ITEM		10
#define OBJECT_TYPE_BOOMERANG			11
#define OBJECT_TYPE_PORTAL				50
#define OBJECT_TYPE_KNIGHT				1000

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines
	
	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	if (texID == TEXTURE_ID_TILE_MAP) {
		this->tileMapWidth = atoi(tokens[5].c_str());
		this->tileMapHeight = atoi(tokens[6].c_str());
	}
	
	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  ->(sprite_id | frame_time)  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations *animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

void CPlayScene::__ParseSection_TILE_MAP(string line)
{
	vector<string> tokens = split(line, ",");//cat chuoi  

	int numberOfTilesInARow = this->tileMapWidth/TILE_WIDTH;
		for (int i = 0; i < tokens.size(); i++)  
		{
			int tileId = atoi(tokens[i].c_str()) - 1;
			int left = (tileId % numberOfTilesInARow) * TILE_WIDTH;
			int top = (tileId / numberOfTilesInARow) * TILE_HEIGHT;
			int right = left + TILE_WIDTH;
			int bottom = top + TILE_HEIGHT;
			int x, y;
			x = i * TILE_WIDTH;
			y = this->tileMapLineY;

			CTile * tile = new CTile(x, y, left, top, right, bottom);
			tileMap.push_back(tile);
		}

		this->tileMapLineY += TILE_HEIGHT;
}

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);
	
	DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_SIMON:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] SIMON object was created before! ");
			return;
		}
		obj = CSimon::GetInstance();
		player = (CSimon*)obj;
		break;
	case OBJECT_TYPE_WHIP: obj = CWhip::GetInstance(); break;
	case OBJECT_TYPE_HEART:
		obj = new CHeartItem();
		CItems::GetInstance()->Add((int)Item::HEART, obj);
		break;
	case OBJECT_TYPE_SMALL_HEART:
		obj = new CSmallHeart();
		CItems::GetInstance()->Add((int)Item::SMALLHEART, obj);
		break;
	case OBJECT_TYPE_BRICK:
	{
		int width = atoi(tokens[4].c_str());
		int height = atoi(tokens[5].c_str());
		obj = new CBrick();
		obj->SetWidth(width);
		obj->SetHeight(height);
		break;
	}
	case OBJECT_TYPE_BRIDGE:
		obj = new CBridge();
		break;
	case OBJECT_TYPE_SECRET_BRICK:
		obj = new CSecretBrick();
		break;
	case OBJECT_TYPE_STAIRS_UP:
		obj = new CStairsUp();
		break;
	case OBJECT_TYPE_STAIRS_DOWN:
		obj = new CStairsDown();
		break;
	case OBJECT_TYPE_FLAMES:
		obj = new CFlame();
		CFlames::GetInstance()->Add((CFlame*)obj);
		break;
	case OBJECT_TYPE_WHIPITEM:
		obj = new CWhipItem();
		CItems::GetInstance()->Add((int)Item::WHIP_ITEM, obj);
		break;
	case OBJECT_TYPE_KNIFE_ITEM:
		obj = new CKnifeItem();
		CItems::GetInstance()->Add((int)Item::KNIFE, obj);
		break;
	case OBJECT_TYPE_BOOMERANG_ITEM:
		obj = new CBoomerangItem();
		CItems::GetInstance()->Add((int)Item::BOOMERANG, obj);
		break;
	case OBJECT_TYPE_KNIFE:
		obj = CKnife::GetInstance();
		CWeapons::GetInstance()->Add((int)Weapon::KNIFE, obj);
		break;
	case OBJECT_TYPE_BOOMERANG:
		obj = CBoomerang::GetInstance();
		CWeapons::GetInstance()->Add((int)Weapon::BOOMERANG, obj);
		break;
	case OBJECT_TYPE_CANDLE:
	{
		int typeObj = atoi(tokens[4].c_str());
		obj = new CCandle();
		obj->SetHoldingItem(typeObj);
		break;
	}
	case OBJECT_TYPE_SMALL_CANDLE:
	{
		int typeObj = atoi(tokens[4].c_str());
		obj = new CSmallCandle();
		obj->SetHoldingItem(typeObj);
		break;
	}
	case OBJECT_TYPE_KNIGHT:
		obj = new CKnight();
		break;
	case OBJECT_TYPE_PORTAL:
	{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);
	objects.push_back(obj);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);
	
	ifstream f;
	f.open(sceneFilePath);
	
	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[TILEMAP]") {
			section = SCENE_SECTION_TILEMAP; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_TILEMAP: __ParseSection_TILE_MAP(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 0, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that SIMON is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		if (objects[i]->GetVisible())
			coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		/*if (objects[i]->GetVisible())*/
			objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow SIMON
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame *game = CGame::GetInstance();
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;
	
	if (cx < 0) 
		cx = 0;/*
	if (cx > game->GetScreenWidth()) 
		cx = game->GetScreenWidth();*/
	CGame::GetInstance()->SetCamPos(cx, cy);
}

void CPlayScene::Render()
{
	for (int i = 0; i < tileMap.size(); i++)
		tileMap[i]->Render();

	for (int i = 0; i < objects.size(); i++)
		if (this->objects[i]->GetVisible())
			objects[i]->Render();

}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (dynamic_cast<CSimon *>(objects[i]) || dynamic_cast<CWhip *>(objects[i])|| dynamic_cast<CKnife *>(objects[i])) 
		{ ; }
		
		else 
		{ delete objects[i]; }
	}
		

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CSimon *simon = ((CPlayScene*)scence)->player;
	if (simon->IsInBridge())
	{
		switch (KeyCode)
		{
		case DIK_K:
			simon->SetState((int)SimonStateID::stateJumpInBridge);
			break;
		case DIK_L:
			if (CGame::GetInstance()->IsKeyDown(DIK_W) && CSimon::GetInstance()->GetSecondWeapons() != (int)Weapon::NONE)
			{
				simon->SetState((int)SimonStateID::stateUseWeaponInBridge);
				break;
			}
			else
			{
				simon->SetState((int)SimonStateID::stateWhippingInBridge);
				break;
			}

		case DIK_A:
			simon->SetState((int)SimonStateID::stateWalkingLeftInBridge);
			break;
		case DIK_D:
			simon->SetState((int)SimonStateID::stateWalkingRightInBridge);
			break;
		}
	}
	else
	{
		switch (KeyCode)
		{
		case DIK_K:
			simon->SetState((int)SimonStateID::stateJump);
			break;
		case DIK_L:
			if (CGame::GetInstance()->IsKeyDown(DIK_W) && CSimon::GetInstance()->GetSecondWeapons() != (int)Weapon::NONE)
			{
				simon->SetState((int)SimonStateID::stateUseWeapon);
				break;
			}
			else
			{
				simon->SetState((int)SimonStateID::stateWhipping);
				break;
			}

		case DIK_A:
			simon->SetState((int)SimonStateID::stateWalkingLeft);
			break;
		case DIK_D:
			simon->SetState((int)SimonStateID::stateWalkingRight);
			break;
		}

	}
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	CSimon *simon = ((CPlayScene*)scence)->player;
	if (simon->IsInBridge())
	{
		simon->SetState((int)SimonStateID::stateIdleInBridge);
	}
	else
	{
		simon->SetState((int)SimonStateID::stateIdle);
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CSimon *simon = ((CPlayScene*)scence)->player;
	if (simon->IsInBridge())
	{
		if (CGame::GetInstance()->IsKeyDown(DIK_S))
		{
			simon->SetState((int)SimonStateID::stateSitInBridge);
		}
		else if (CGame::GetInstance()->IsKeyDown(DIK_D))
		{
			simon->SetState((int)SimonStateID::stateWalkingRightInBridge);
		}
		else if (CGame::GetInstance()->IsKeyDown(DIK_A))
		{
			simon->SetState((int)SimonStateID::stateWalkingLeftInBridge);
		}
		else simon->SetState((int)SimonStateID::stateIdleInBridge);
	}
	else
	{
		if (CGame::GetInstance()->IsKeyDown(DIK_S))
		{
			simon->SetState((int)SimonStateID::stateGoingDownStairsLeft);
			simon->SetState((int)SimonStateID::stateSit);
		}
		else if (CGame::GetInstance()->IsKeyDown(DIK_D))
		{
			simon->SetState((int)SimonStateID::stateWalkingRight);
		}
		else if (CGame::GetInstance()->IsKeyDown(DIK_A))
		{
			simon->SetState((int)SimonStateID::stateWalkingLeft);
		}
		else if (CGame::GetInstance()->IsKeyDown(DIK_S))
		{
			simon->SetState((int)SimonStateID::stateGoingDownStairsLeft);
		}
		else if (CGame::GetInstance()->IsKeyDown(DIK_W))
		{
			simon->SetState((int)SimonStateID::stateGoingUpStairsRight);
		}
		else simon->SetState((int)SimonStateID::stateIdle);
	}
}