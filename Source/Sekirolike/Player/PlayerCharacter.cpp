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

	PlayerInput = Cast<APlayerInputManager>(GetController());
	if (PlayerInput == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PlayerInput is nullptr"));
	}
	Animator = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (PlayerInput == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Animator is nullptr"));
	}
}

void APlayerCharacter::Locomotion(float deltaTime)
{
	if (LockState)
	{

	}
	else
	{
		// Calculate the movement direction and speed
		FVector2f temp = FVector2f(PlayerInput->MappedDright, PlayerInput->MappedDup);
		Dmag = FMath::Sqrt(temp.X * temp.X + temp.Y * temp.Y);

		FRotator rotator = GetControlRotation();
		FRotator yawRotator = FRotator(0, rotator.Yaw, 0);
		FVector forward = FQuat(yawRotator).GetForwardVector();
		FVector right = FQuat(yawRotator).GetRightVector();
		Dvec = temp.X * right + temp.Y * forward;

		Animator->Right = 0;
		Animator->Forward = FMath::FInterpTo(Animator->Forward, FMath::Clamp(Dmag * 2.0f, (!PlayerInput->Sprint ? 0.0f : 1.0f), (!PlayerInput->Sprint ? 1.0f : 2.0f)), deltaTime, 5.0f);
		AddMovementInput(Dvec, FMath::Clamp(Dmag, (!PlayerInput->Sprint ? 0.0f : 0.5f), (!PlayerInput->Sprint ? 0.5f : 1.0f)));
	}
}

void APlayerCharacter::CameraControl(float deltaTime)
{
	if (LockState)
	{

	}
	else
	{
		FRotator currentRotator = Controller->GetControlRotation();
		currentRotator.Pitch -= PlayerInput->Jup * CameraVerticalSpeed * deltaTime;
		currentRotator.Pitch = FMath::ClampAngle(currentRotator.Pitch, CameraMinEulerX, CameraMaxEulerX);
		currentRotator.Yaw += PlayerInput->Jright * CameraHorizontalSpeed * deltaTime;
		Controller->SetControlRotation(currentRotator);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Locomotion(DeltaTime);

	CameraControl(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

