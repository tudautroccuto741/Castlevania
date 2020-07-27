#include "Numbers.h"

CNumbers * CNumbers::__instance = NULL;

void CNumbers::Add(CNumber * number)
{
	number->SetVisible(false);
	numbers.push_back(number);
}

void CNumbers::ShowNumbers(int ani, float x, float y)
{
	CNumber * number = NULL;

	for (UINT i = 0; i < numbers.size(); i++)
	{
		if (numbers[i]->GetVisible() == false)
		{
			number = numbers[i];
			i++;
			break;
		}
	}
	if (number != NULL)
	{
		number->SetPosition(x, y);
		number->currentAniID = ani;
		number->SetVisible(true);
	}

}

void CNumbers::Clear()
{
	numbers.clear();
}

CNumbers * CNumbers::GetInstance()
{
	if (__instance == NULL)
		__instance = new CNumbers();

	return __instance;
}
