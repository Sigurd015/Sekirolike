// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "Sekirolike/Components/Combat/PlayerCombatComponent.h"
#include "Sekirolike/Utils/Math.h"
#include "Sekirolike/Input/CustomInputComponent.h"
#include "Sekirolike/DataAsset/Input/InputConfig.h"
#include "Sekirolike/DataAsset/StartUpData/StartUpData.h"
#include "Sekirolike/GamePlayTag/GamePlayeTags.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 10.0f;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	PlayerCombatComponent = CreateDefaultSubobject<UPlayerCombatComponent>(TEXT("PlayerCombatComponent"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, "Setting up input");

	checkf(InputConfig, TEXT("InputConfig is nullptr"));

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);
	Subsystem->AddMappingContext(InputConfig->DefaultMappingContext, 0);

	UCustomInputComponent* CustomInputComponent = CastChecked<UCustomInputComponent>(PlayerInputComponent);
	CustomInputComponent->BindNativeInputAction(InputConfig, GamePlayTags::InputTag_Move, ETriggerEvent::Triggered,
	                                            this,
	                                            &ThisClass::Move);
	CustomInputComponent->BindNativeInputAction(InputConfig, GamePlayTags::InputTag_Look, ETriggerEvent::Triggered,
	                                            this,
	                                            &ThisClass::Look);
	CustomInputComponent->BindNativeInputAction(InputConfig, GamePlayTags::InputTag_Sprint_Doge,
	                                            ETriggerEvent::Triggered,
	                                            this,
	                                            &ThisClass::StartSprint);
	CustomInputComponent->BindNativeInputAction(InputConfig, GamePlayTags::InputTag_Sprint_Doge,
	                                            ETriggerEvent::Completed,
	                                            this,
	                                            &ThisClass::StopSprinting);
	CustomInputComponent->BindNativeInputAction(InputConfig, GamePlayTags::InputTag_Sprint_Doge,
	                                            ETriggerEvent::Canceled,
	                                            this,
	                                            &ThisClass::Dodge);
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!CharacterStartUpData.IsNull())
	{
		if (UStartUpData* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(AbilitySystemComponent);
		}
	}
}

void APlayerCharacter::Move(const FInputActionValue& InputActionValue)
{
	FVector2D MovementInput = FVector2D(InputActionValue.Get<FVector2D>().X, InputActionValue.Get<FVector2D>().Y);
	const FRotator MovementRotation(0.0f, GetControlRotation().Yaw, 0.0f);

	if (!MovementInput.IsNearlyZero())
	{
		double Dmag = 0.0;
		FVector Dvec = FVector::ZeroVector;
		Helper::Math::EllipticalGridMapping(MovementInput, MovementRotation.RotateVector(FVector::ForwardVector),
		                                    MovementRotation.RotateVector(FVector::RightVector), Dmag, Dvec);
		AddMovementInput(Dvec, Dmag);
	}
}

void APlayerCharacter::Look(const FInputActionValue& value)
{
	const FVector2D LookAxisInput = value.Get<FVector2D>();

	if (LookAxisInput.X != 0.0f)
	{
		AddControllerYawInput(LookAxisInput.X);
	}

	if (LookAxisInput.Y != 0.0f)
	{
		AddControllerPitchInput(LookAxisInput.Y);
	}
}

void APlayerCharacter::StartSprint(const FInputActionInstance& instance)
{
	if (instance.GetElapsedTime() > 0.1f)
		GetCharacterMovement()->MaxWalkSpeed = 400.0f;
}

void APlayerCharacter::StopSprinting(const FInputActionInstance& instance)
{
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
}

void APlayerCharacter::Dodge(const FInputActionInstance& instance)
{
}
