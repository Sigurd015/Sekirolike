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
#include "Sekirolike/Weapon/WeaponActor.h"

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

	FTransform katanaST = GetMesh()->GetSocketTransform(KatanaSocketName);
	KatanaActor = GetWorld()->SpawnActor<AWeaponActor>(KatanaToSpawn, katanaST);
	FTransform scabbardST = GetMesh()->GetSocketTransform(ScabbardSocketName);
	ScabbardActor = GetWorld()->SpawnActor<AWeaponActor>(ScabbardToSpawn, scabbardST);

	KatanaActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, KatanaSocketName);
	ScabbardActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale,
	                                 ScabbardSocketName);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Locomotion(DeltaTime);
	CameraControl(DeltaTime);

	//Debug
#if WITH_EDITOR
	//Draw direction
	FVector startLocation = GetActorLocation();
	startLocation.Z = 10.0f;
	DrawDebugDirectionalArrow(GetWorld(), startLocation, startLocation + Dvec * 200.0f, 100.0f, FColor::Red, false, -1,
	                          0, 5.0f);
	DrawDebugDirectionalArrow(GetWorld(), startLocation, startLocation + GetActorForwardVector() * 100.0f, 100.0f,
	                          FColor::Green, false, -1, 0, 5.0f);
#endif
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

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(SprintDodgeAction, ETriggerEvent::Triggered, this,
		                                   &APlayerCharacter::StartSprint);
		EnhancedInputComponent->BindAction(SprintDodgeAction, ETriggerEvent::Completed, this,
		                                   &APlayerCharacter::StopSprinting);
		EnhancedInputComponent->BindAction(SprintDodgeAction, ETriggerEvent::Canceled, this,
		                                   &APlayerCharacter::Dodge);

		EnhancedInputComponent->BindAction(LockAction, ETriggerEvent::Triggered, this, &APlayerCharacter::LockUnlock);

		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Attack);
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
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, "Playing Dodge Animation");

	if (LockState)
	{
		if (FMath::Abs(Forward) > FMath::Abs(Right))
		{
			if (Forward > 0.1f)
				AnimInstance->Montage_Play(DodgeForwardAnimMontage, 1.0f);
			else
				AnimInstance->Montage_Play(DodgeBackwardAnimMontage, 1.0f);
		}
		else
		{
			if (Right > 0.1f)
				AnimInstance->Montage_Play(DodgeRightAnimMontage, 1.0f);
			else
				AnimInstance->Montage_Play(DodgeLeftAnimMontage, 1.0f);
		}
	}
	else
	{
		AnimInstance->Montage_Play(DodgeForwardAnimMontage, 1.0f);
	}
}

void APlayerCharacter::Attack(const FInputActionInstance& instance)
{
	static int32 attackIndex = 1;
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, "Playing Attack Animation");

	switch (attackIndex)
	{
	case 1:
		AnimInstance->Montage_Play(Attack1AnimMontage, 1.0f);
		break;
	case 2:
		AnimInstance->Montage_Play(Attack2AnimMontage, 1.0f);
		break;
	case 3:
		AnimInstance->Montage_Play(Attack3AnimMontage, 1.0f);
		break;
	case 4:
		AnimInstance->Montage_Play(Attack4AnimMontage, 1.0f);
		break;
	}
	attackIndex++;
	if (attackIndex > 4)
		attackIndex = 1;
}

void APlayerCharacter::LockUnlock()
{
	GEngine->AddOnScreenDebugMessage(1, 2, FColor::Red, "Locking");

	if (Target != nullptr)
	{
		Target = nullptr;
		LockState = false;
		return;
	}

	FVector startLocation = GetActorLocation();
	FVector endLocation = startLocation + GetActorForwardVector() * LockTargetDistance;

	FHitResult HitResult;
	TArray<AActor*> IgnoresActors;
	IgnoresActors.Reserve(1);
	IgnoresActors.Add(this);
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
	ObjectTypesArray.Reserve(1);
	ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	bool hit = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), startLocation, endLocation,
	                                                             LockTargetRadius,
	                                                             ObjectTypesArray,
	                                                             false, IgnoresActors, EDrawDebugTrace::ForDuration,
	                                                             HitResult,
	                                                             true);
	if (hit)
	{
		Target = HitResult.GetActor();
		FVector origin;
		FVector boxExtent;
		Target->GetActorBounds(false, origin, boxExtent);
		TargetHeight = boxExtent.Z;
		LockState = true;

		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red,
		                                 FString::Printf(TEXT("Obj name:%s"), *Target->GetName()));
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red,
		                                 FString::Printf(TEXT("Obj height:%f"), TargetHeight));
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
		GetCharacterMovement()->bUseControllerDesiredRotation = true;

		FVector localDevc = GetActorTransform().InverseTransformVector(Dvec);
		Right = localDevc.Y * (!Sprint ? 1.0f : 2.0f);
		Forward = localDevc.X * (!Sprint ? 1.0f : 2.0f);

		if (!LockPlanar)
			AddMovementInput(Dvec, FMath::Clamp(Dmag, (!Sprint ? 0.0f : 0.5f), (!Sprint ? 0.5f : 1.0f)));
	}
	else
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;

		Right = 0;
		Forward = FMath::FInterpTo(Forward, FMath::Clamp(Dmag * 2.0f, (!Sprint ? 0.0f : 1.0f), (!Sprint ? 1.0f : 2.0f)),
		                           deltaTime, 5.0f);

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
		FVector startLocation = GetActorLocation();
		FVector targetLocation = Target->GetActorLocation();
		FRotator targetRot = UKismetMathLibrary::FindLookAtRotation(startLocation, targetLocation);
		targetRot.Pitch -= LockTargetHeightOffset;
		GetController()->SetControlRotation(targetRot);

		if (FVector::Distance(targetLocation, GetActorLocation()) > LockTargetDistance)
			LockUnlock();
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
