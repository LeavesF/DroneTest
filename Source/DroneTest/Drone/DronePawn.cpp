// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneTest/Drone/DronePawn.h"

#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

// Sets default values
ADronePawn::ADronePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DroneMesh"));
	Mesh->SetCollisionProfileName(UCollisionProfile::Vehicle_ProfileName);
	Mesh->BodyInstance.bSimulatePhysics = false;
	Mesh->BodyInstance.bNotifyRigidBodyCollision = true;
	Mesh->BodyInstance.bUseCCD = true;
	Mesh->SetGenerateOverlapEvents(true);
	Mesh->SetCanEverAffectNavigation(false);
	RootComponent = Mesh;*/

	//droneMovement = CreateDefaultSubobject<UCharacterMovementComponent>(TEXT("DroneMovementComponent"));
	//droneMovement->SetIsReplicated(true); // Enable replication by default
	//droneMovement->UpdatedComponent = Mesh;
}

// Called when the game starts or when spawned
void ADronePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADronePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Controller != nullptr and !FMath::IsNearlyZero(curRotationVelocity))
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(curRotationVelocity);
		if(!bIsSteering)
		{
			curRotationVelocity = FMath::Lerp(curRotationVelocity, 0, 0.05f);
		}
	}
}

// Called to bind functionality to input
void ADronePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// steering 
		EnhancedInputComponent->BindAction(IA_Fly, ETriggerEvent::Triggered, this, &ADronePawn::OnFlying);

		// break 
		EnhancedInputComponent->BindAction(IA_Steer, ETriggerEvent::Triggered, this, &ADronePawn::OnSteering);
		EnhancedInputComponent->BindAction(IA_Steer, ETriggerEvent::Started, this, &ADronePawn::OnSteerStart);
		EnhancedInputComponent->BindAction(IA_Steer, ETriggerEvent::Completed, this, &ADronePawn::OnSteerEnd);

		// throttle 
		EnhancedInputComponent->BindAction(IA_UpDown, ETriggerEvent::Triggered, this, &ADronePawn::OnUpDown);
	}
}

//UCharacterMovementComponent* ADronePawn::GetMovementComponent()
//{
//	if (droneMovement)
//	{
//		return droneMovement;
//	}
//	return nullptr;
//}

void ADronePawn::OnFlying(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D movementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// find out which way is forward
		const FRotator VelocityRotation = GetVelocity().GetSafeNormal().Rotation();
		const FRotator YawVelocityRotation(0, VelocityRotation.Yaw, 0);

		// get right vector 
		const FVector RightDirection = GetActorRightVector();

		// add movement 
		AddMovementInput(ForwardDirection, movementVector.X);
		AddMovementInput(RightDirection, movementVector.Y);
		/*if (droneMovement)
		{
			droneMovement->AddInputVector(ForwardDirection * movementVector.Y, false);
			droneMovement->AddInputVector(RightDirection * movementVector.X, false);
		}*/
	}
}

void ADronePawn::OnSteering(const FInputActionValue& Value)
{
	// input is a Vector2D
	float horizontalValue = Value.Get<float>() * 0.7f;
	curRotationVelocity = FMath::Lerp(curRotationVelocity, horizontalValue, 0.01f);
	UE_LOG(LogTemp, Display, TEXT("curRotationVelocity:%f"), curRotationVelocity);

	//if (Controller != nullptr)
	//{
	//	// add yaw and pitch input to controller
	//	AddControllerYawInput(curRotationVelocity);
	//	//AddControllerPitchInput(horizontalValue);
	//}
}

void ADronePawn::OnSteerStart()
{
	bIsSteering = true;
}

void ADronePawn::OnSteerEnd()
{
	bIsSteering = false;
}

void ADronePawn::OnUpDown(const FInputActionValue& Value)
{
	float verticalValue = Value.Get<float>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector UpDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Z);

		AddMovementInput(UpDirection, verticalValue);
		//UE_LOG(LogTemp, Warning, TEXT("VerticalValue: %f"), verticalValue);
	}
}

