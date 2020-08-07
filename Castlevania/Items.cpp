#include "Items.h"
#include "debug.h"

CItems * CItems::__instance = NULL;

//	Add the corresponding item with the item name
void CItems::Add(int itemName, LPGAMEOBJECT item)
{
	items[itemName].push_back(item);
}	

//	Check if the object is holding item, drop it if has

void CItems::CheckAndDrop(LPGAMEOBJECT object)
{
	int item = object->GetHoldingItem();
	if (item != (int)Item::NONE)
	{
		if (item == (int)Item::BALL)
		{
			Drop(item, 1200, 37);
		}
		else
		{
			float x, y;
			object->GetPosition(x, y);
			Drop(item, x, y);
		}
	}
}

//	Get the item according to the given name and set it the gien position

void CItems::Drop(int itemName, float x, float y)
{
	if (items[itemName].empty())
		DebugOut(L"\n[ERROR] No items with the given name found (Item enum: %d)", (int)itemName);

	else
	{
		for (auto i = items[itemName].begin(); i != items[itemName].end(); ++i)
		{
			if ((*i)->GetVisible()==false)
			{
				(*i)->SetPosition(x, y);
				(*i)->SetVisible(true);
				break;
			}
		}
	}
}

void CItems::Clear()
{
	items.clear();
}

CItems * CItems::GetInstance()
{
	if (__instance == NULL)
		__instance = new CItems();

	return __instance;
}
