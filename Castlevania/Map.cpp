#pragma once
#include "Map.h"

CMap* CMap::__instance = NULL;
CMap* CMap::GetInstance() {
	if (__instance == NULL)
		__instance = new CMap();
	return __instance;
};
