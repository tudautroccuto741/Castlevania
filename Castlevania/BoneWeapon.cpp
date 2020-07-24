#include "BoneWeapon.h"
#include "Weapons.h"

#define BONE_POINT_AWARD		100
#define BONE_DAMAGE				2
#define BONE_DEFAULT_HEALTH		1


void CBoneWeapon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BONE_BBOX_WIDTH;
	bottom = y + BONE_BBOX_HEIGHT;
}

void CBoneWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy += 0.0016 * this->dt;


	// If the dagger go out the viewport
	if (this->IsInViewport() == false)
		SetVisible(false);

	// Update the position
	x += dx;
	y += dy;
}

void CBoneWeapon::SetVisible(bool visible)
{
	CGameObject::SetVisible(visible);
	if (visible)
	{
		// BONE's horizontally movement
		vx = (nx > 0) ?
			BONE_SPEED_VX :
			-BONE_SPEED_VX;

		vy = -BONE_SPEED_VY;
	}
}

void CBoneWeapon::Render()
{
	// Choose matched animation
	currentAniID = (nx > 0) ?
		BoneWeaponAniID::FLYING_RIGHT :
		BoneWeaponAniID::FLYING_LEFT;
	if (visible)
	{
		CGameObject::Render();
	}
}

CBoneWeapon::CBoneWeapon()
{
	visible = false;
	damage = BONE_DAMAGE;
}
