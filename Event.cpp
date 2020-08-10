#include "stdafx.h"
#include "Event.h"

void StopCamera::EventStart(float centerX, float centerY)
{
	CAMERAMANAGER->setX(centerX);
	CAMERAMANAGER->setY(centerY);
}

bool StopCamera::EventUpdate()
{
	return false;
}
