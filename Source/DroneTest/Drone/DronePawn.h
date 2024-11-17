// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DroneTest/Drone/DroneMovementComponent.h"
#include "DronePawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class UChaosWheeledVehicleMovementComponent;
class UCharacterMovementComponent;
struct FInputActionValue;

UCLASS()
class DRONETEST_API ADronePawn : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADronePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//virtual UCharacterMovementComponent* GetMovementComponent();

private:
	/**  The main skeletal mesh associated with this Vehicle */
	/*UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> Mesh;*/

protected:
	/** Steering Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* IA_Fly;

	/** Throttle Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* IA_UpDown;

	/** Brake Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* IA_Steer;

protected:
	/** Handles Flying input */
	void OnFlying(const FInputActionValue& Value);

	/** Handles steering input */
	void OnSteering(const FInputActionValue& Value);

	void OnSteerStart();

	void OnSteerEnd();

	/** Handles UpDown input */
	void OnUpDown(const FInputActionValue& Value);

private:
	bool bIsSteering = false;
	float curRotationVelocity = 0;

public:
	/** DefaultPawn movement component */
	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCharacterMovementComponent> droneMovement;
};
