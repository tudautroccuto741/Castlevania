#pragma once
#include "GameObject.h"
#include <unordered_map>


using namespace std;

class CItems
{
	unordered_map<int, vector<LPGAMEOBJECT>> items;
	static CItems * __instance;
	
public:

	void Add(int itemName, LPGAMEOBJECT item);
	void CheckAndDrop(LPGAMEOBJECT gameObject);			// Check if the given object is holding item, drop it if yes
	void Drop(int iteamName, float x, float y);
	CItems() { ; }
	static CItems * GetInstance();
};
