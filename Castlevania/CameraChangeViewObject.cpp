#include "CameraChangeViewObject.h"
CCameraChangeViewObject * CCameraChangeViewObject::__instance = NULL;

void CCameraChangeViewObject::Render()
{

}

void CCameraChangeViewObject::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + CAMERA_CHANGE_VIEW_BBOX_WIDTH;
	b = y + CAMERA_CHANGE_VIEW_BBOX_HEIGHT;
}

CCameraChangeViewObject::CCameraChangeViewObject()
{
	this->currentAniID = (int)CameraChangeViewObjectAniID::idle;
	visible = true;
}

CCameraChangeViewObject *CCameraChangeViewObject::GetInstance()
{
	if (__instance == NULL) __instance = new CCameraChangeViewObject();
	return __instance;
}