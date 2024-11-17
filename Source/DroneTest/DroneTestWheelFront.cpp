// Copyright Epic Games, Inc. All Rights Reserved.

#include "DroneTestWheelFront.h"
#include "UObject/ConstructorHelpers.h"

UDroneTestWheelFront::UDroneTestWheelFront()
{
	AxleType = EAxleType::Front;
	bAffectedBySteering = true;
	MaxSteerAngle = 40.f;
}