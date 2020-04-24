#include "Items.h"
#include "debug.h"

CItems * CItems::__instance = NULL;

/*
	Add the given item to the collection according to item name
*/
void CItems::Add(int itemName, LPGAMEOBJECT item)
{
	item->SetVisible(false);
	items[itemName].push_back(item);
}	

/*
	Check if the gameobject is holding item, drop it if has
*/
void CItems::CheckAndDrop(LPGAMEOBJECT object)
{
	int item = object->GetHoldingItem();
	if (item != (int)Item::NONE)
	{
		float x, y;
		object->GetPosition(x, y);
		Drop(item, x, y);
	}
}

/*
	Get the item according to the given name and set it the gien position
*/
void CItems::Drop(int itemName, float x, float y)
{
	if (items[itemName].empty())
		DebugOut(L"\n[ERROR] No items with the given name found (Item enum: %d)", (int)itemName);

	else
	{
		for (auto it = items[itemName].begin(); it != items[itemName].end(); ++it)
		{
			if ((*it)->GetVisible()==false)
			{
				(*it)->SetPosition(x, y);
				(*it)->SetVisible(true);
				break;
			}
		}
	}
}

CItems * CItems::GetInstance()
{
	if (__instance == NULL)
		__instance = new CItems();

	return __instance;
}
