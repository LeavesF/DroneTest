// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DroneTestPawn.h"
#include "DroneTestSportsCar.generated.h"

/**
 *  Sports car wheeled vehicle implementation
 */
UCLASS(abstract)
class DRONETEST_API ADroneTestSportsCar : public ADroneTestPawn
{
	GENERATED_BODY()
	
public:

	ADroneTestSportsCar();
};
