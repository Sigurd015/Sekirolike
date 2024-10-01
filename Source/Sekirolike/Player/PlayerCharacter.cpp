// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "PlayerInputManager.h"
#include "PlayerAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void APlayerCharacter::Movement(float deltaTime)
{
	if (LockState)
	{

	}
	else
	{
		float speed = PlayerInput->Dmag * (!PlayerInput->Run ? WalkSpeed : WalkSpeed * RunMultiplier);
		Animator->Right = 0;
		Animator->Forward = FMath::FInterpTo(Animator->Forward, speed, deltaTime, 5.0f);
		AddMovementInput(PlayerInput->Dvec, speed);
	}
}

void APlayerCharacter::CameraControl(float deltaTime)
{
	if (LockState)
	{

	}
	else
	{
		AddControllerPitchInput(PlayerInput->Jup);
		AddControllerYawInput(PlayerInput->Jright);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

