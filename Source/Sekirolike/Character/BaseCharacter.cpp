// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Sekirolike/Weapon/WeaponActor.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(34.0f, 88.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
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
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
