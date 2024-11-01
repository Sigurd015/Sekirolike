// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputAction.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(34.0f, 88.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraRig"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 10.0f;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

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

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		MoveActionBinding = &EnhancedInputComponent->BindActionValue(MoveAction);
		LookActionBinding = &EnhancedInputComponent->BindActionValue(LookAction);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &APlayerCharacter::StartSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Ongoing, this, &APlayerCharacter::OnSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopSprinting);
	}
}

//void  APlayerCharacter::DodgeTrigger(const FInputActionInstance& instance)
//{
//	Dodge = true;
//
//	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Dodge " + FString::SanitizeFloat(instance.GetElapsedTime()));
//
//	//LaunchCharacter(Dvec * 1000, true, false);
//}

void APlayerCharacter::StartSprint(const FInputActionInstance& instance)
{
	Sprint = true;
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Dodge " + FString::SanitizeFloat(instance.GetElapsedTime()));
}

void APlayerCharacter::OnSprint(const FInputActionInstance& instance)
{
	Sprint = true;
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Dodge " + FString::SanitizeFloat(instance.GetElapsedTime()));
}

void APlayerCharacter::StopSprinting(const FInputActionInstance& instance)
{
	Sprint = false;
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Dodge " + FString::SanitizeFloat(instance.GetElapsedTime()));
}

// Elliptical Grid Mapping
// See: https://arxiv.org/ftp/arxiv/papers/1509/1509.06344.pdf
void APlayerCharacter::GridMapping(float deltaTime)
{
	const FVector2D inputValue = MoveActionBinding->GetValue().Get<FVector2D>();
	float dup = inputValue.Y;
	float dright = inputValue.X;

	FVector2f temp = FVector2f::ZeroVector;
	temp.X = dright * FMath::Sqrt(1.0f - 0.5f * (dup * dup));
	temp.Y = dup * FMath::Sqrt(1.0f - 0.5f * (dright * dright));

	Dmag = FMath::Sqrt(temp.X * temp.X + temp.Y * temp.Y);

	FRotator rotator = GetControlRotation();
	FRotator yawRotator = FRotator(0, rotator.Yaw, 0);
	FVector forward = FQuat(yawRotator).GetForwardVector();
	FVector right = FQuat(yawRotator).GetRightVector();
	Dvec = temp.X * right + temp.Y * forward;
}

void APlayerCharacter::Locomotion(float deltaTime)
{
	// TODO: May change to use animation notifications 
	LockPlanar = GetCharacterMovement()->IsFalling();

	if (LockState)
	{

	}
	else
	{
		// Calculate the movement direction and speed
		GridMapping(deltaTime);

		Right = 0;
		Forward = FMath::FInterpTo(Forward, FMath::Clamp(Dmag * 2.0f, (!Sprint ? 0.0f : 1.0f), (!Sprint ? 1.0f : 2.0f)), deltaTime, 5.0f);

		if (!LockPlanar)
			AddMovementInput(Dvec, FMath::Clamp(Dmag, (!Sprint ? 0.0f : 0.5f), (!Sprint ? 0.5f : 1.0f)));
	}
}

void APlayerCharacter::CameraControl(float deltaTime)
{
	const FVector2D inputValue = LookActionBinding->GetValue().Get<FVector2D>();
	float jup = inputValue.Y;
	float jright = inputValue.X;

	if (LockState)
	{

	}
	else
	{
		FRotator currentRotator = Controller->GetControlRotation();
		currentRotator.Pitch -= jup * CameraVerticalSpeed * deltaTime;
		currentRotator.Pitch = FMath::ClampAngle(currentRotator.Pitch, CameraMinEulerX, CameraMaxEulerX);
		currentRotator.Yaw += jright * CameraHorizontalSpeed * deltaTime;
		Controller->SetControlRotation(currentRotator);
	}
}
