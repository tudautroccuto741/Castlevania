#include "DrawBoard.h"
#include "Sprites.h"

void CDrawBoard::DrawNumber(int max, float x, float y, int s)
{
	string str = to_string(s);

	for (int i = 0; i < max - str.size(); i++)
	{
		CSprites::GetInstance()->Get(700)->Draw(x, y, 255);
		x += 15;
	}
	for (int i = 0; i < str.size(); i++)
	{
		CSprites::GetInstance()->Get(700 + convert(str[i]))->Draw(x, y, 255);
		x += 15;
	}
}
void CDrawBoard::DrawEnergyBar(float x, float y, int type, int s)
{
	CSprites* sprites = CSprites::GetInstance();
	CSprite* sprite1 = sprites->Get(711);
	CSprite* sprite2 = NULL;
	if (type == 0)
		sprite2 = sprites->Get(710);
	else
		sprite2 = sprites->Get(712);
	for (int i = 0; i < s; i++)
	{
		sprite2->Draw(x, y);
		x += 8;
	}
	for (int i = 0; i < 16 - s; i++)
	{
		sprite1->Draw(x, y);
		x += 8;
	}
	sprites = NULL;
	sprite1 = NULL;
	sprite2 = NULL;
}

int CDrawBoard::convert(char c)
{
	return c - '0';
}