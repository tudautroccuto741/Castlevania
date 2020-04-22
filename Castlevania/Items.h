#pragma once
#include "GameObject.h"
#include <unordered_map>


using namespace std;

class CItems
{
	unordered_map<Item, vector<LPGAMEOBJECT>> items;
	static CItems * __instance;
	
public:

	void Add(Item itemName, LPGAMEOBJECT item);
	void CheckAndDrop(LPGAMEOBJECT gameObject);			// Check if the given object is holding item, drop it if yes
	void Drop(Item iteamName, float x, float y);
	CItems() { ; }
	static CItems * GetInstance();
};

