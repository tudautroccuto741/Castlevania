#pragma once
#include "Flea.h"
#include "GameObject.h"
#define POSITION_FLEA_TO_VISIBLE 1200

class CSpawnFlea
{
	unordered_map<int, vector<LPGAMEOBJECT>> fleas;

	static CSpawnFlea * __instance;
public:

	void Add(int fleaname, LPGAMEOBJECT flea);
	void ShowFlea();
	void Clear();
	LPGAMEOBJECT GetFlea(int flea);
	CSpawnFlea() { ; }
	static CSpawnFlea * GetInstance();
};