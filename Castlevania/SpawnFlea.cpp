#include "SpawnFlea.h"
#include "debug.h"

CSpawnFlea * CSpawnFlea::__instance = NULL;

void CSpawnFlea::Add(int fleaname, LPGAMEOBJECT flea)
{
	flea->SetVisible(false);
	fleas[fleaname].push_back(flea);
}

/*
	Show a flame at the center position of the destroyed object given.
*/
void CSpawnFlea::ShowFlea()
{
	LPGAMEOBJECT flea = GetFlea((int)Monsters::FLEA);
	if (flea == NULL)
	{
		return;
	}
	else
	{
		flea->SetVisible(true);
	}
}

LPGAMEOBJECT CSpawnFlea::GetFlea(int flea)
{
	if (fleas[flea].empty())
		DebugOut(L"\n[ERROR] not found ");
	else
	{
		for (auto i = fleas[flea].begin(); i != fleas[flea].end(); ++i)
		{
			return (*i);
			break;
		}
	}
}

void CSpawnFlea::Clear()
{
	fleas.clear();
}

CSpawnFlea * CSpawnFlea::GetInstance()
{
	if (__instance == NULL)
		__instance = new CSpawnFlea();

	return __instance;
}
