// Copyright Epic Games, Inc. All Rights Reserved.

#include "DroneTestWheelRear.h"
#include "UObject/ConstructorHelpers.h"

UDroneTestWheelRear::UDroneTestWheelRear()
{
	AxleType = EAxleType::Rear;
	bAffectedByHandbrake = true;
	bAffectedByEngine = true;
}