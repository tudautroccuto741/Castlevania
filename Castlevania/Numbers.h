#pragma once
#include "Number.h"

class CNumbers
{
	static CNumbers * __instance;
	vector<CNumber *> numbers;

public:

	void Add(CNumber * number);
	void ShowNumbers(int ani, float x, float y);
	void Clear();
	static CNumbers * GetInstance();

};

