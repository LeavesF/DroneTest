// Copyright Epic Games, Inc. All Rights Reserved.

#include "DroneTestGameMode.h"
#include "DroneTestPlayerController.h"

ADroneTestGameMode::ADroneTestGameMode()
{
	PlayerControllerClass = ADroneTestPlayerController::StaticClass();
}
