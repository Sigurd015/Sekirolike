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
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

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

	AnimInstance = GetMesh()->GetAnimInstance();
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
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		MoveActionBinding = &EnhancedInputComponent->BindActionValue(MoveAction);
		LookActionBinding = &EnhancedInputComponent->BindActionValue(LookAction);

		EnhancedInputComponent->BindAction(LockAction, ETriggerEvent::Triggered, this, &APlayerCharacter::LockUnlock);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this,
		                                   &APlayerCharacter::StartSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this,
		                                   &APlayerCharacter::StopSprinting);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Canceled, this,
		                                   &APlayerCharacter::Dodge);
	}
}

void APlayerCharacter::StartSprint(const FInputActionInstance& instance)
{
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, "Sprinting");
	instance.GetElapsedTime() > 0.1f ? Sprint = true : Sprint = false;
}

void APlayerCharacter::StopSprinting(const FInputActionInstance& instance)
{
	Sprint = false;
}

void APlayerCharacter::Dodge(const FInputActionInstance& instance)
{
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, "Playing Dodge Forward Animation");

	if (LockState)
	{
	}
	else
	{
		AnimInstance->Montage_Play(DodgeForwardAnimMontage, 1.0f);
	}
}

void APlayerCharacter::LockUnlock()
{
	GEngine->AddOnScreenDebugMessage(1, 2, FColor::Red, "Locking");

	if (TargetActor != nullptr)
	{
		TargetActor = nullptr;
		LockState = false;
		return;
	}

	FVector startLocation = GetActorLocation();
	FRotator rotator = GetControlRotation();
	FVector forward = GetMesh()->GetForwardVector();
	FVector endLocation = startLocation + forward * LockTargetDistance;

	FHitResult HitResult;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
	TArray<AActor*> IgnoresActors;
	IgnoresActors.Add(this);
	ObjectTypesArray.Reserve(1);
	ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	bool hit = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), startLocation, endLocation, SphereRadius,
	                                                             ObjectTypesArray,
	                                                             false, IgnoresActors, EDrawDebugTrace::ForDuration,
	                                                             HitResult,
	                                                             true);
	if (hit)
	{
		TargetActor = HitResult.GetActor();
		LockState = true;
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red,
		                                 FString::Printf(TEXT("Obj name:%s"), *HitResult.GetActor()->GetName()));
	}
}

// Elliptical Grid Mapping
// See: https://arxiv.org/ftp/arxiv/papers/1509/1509.06344.pdf
void APlayerCharacter::GridMapping()
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

	// Calculate the movement direction and speed
	GridMapping();

	if (LockState)
	{
		GetCharacterMovement()->bOrientRotationToMovement = false;
		FVector location = GetActorLocation();
		FVector targetLocation = TargetActor->GetActorLocation();
		FRotator targetRot = UKismetMathLibrary::FindLookAtRotation(location, targetLocation);
		GetController()->SetControlRotation(targetRot);

		FVector localDevc = GetActorTransform().InverseTransformVector(Dvec);
		Right = localDevc.X * (!Sprint ? 1.0f : 2.0f);
		Forward = localDevc.Z * (!Sprint ? 1.0f : 2.0f);

		if (!LockPlanar)
		{
		}
		AddMovementInput(Dvec, FMath::Clamp(Dmag, (!Sprint ? 0.0f : 0.5f), (!Sprint ? 0.5f : 1.0f)));
	}
	else
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;
		Right = 0;
		Forward = FMath::FInterpTo(Forward, FMath::Clamp(Dmag * 2.0f, (!Sprint ? 0.0f : 1.0f), (!Sprint ? 1.0f : 2.0f)),
		                           deltaTime, 5.0f);

		if (!LockPlanar)
		{
		}
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
