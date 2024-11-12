// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Sekirolike/Weapon/WeaponActor.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
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
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	FTransform katanaST = GetMesh()->GetSocketTransform(KatanaSocketName);
	KatanaActor = GetWorld()->SpawnActor<AWeaponActor>(KatanaToSpawn, katanaST);
	FTransform scabbardST = GetMesh()->GetSocketTransform(ScabbardSocketName);
	ScabbardActor = GetWorld()->SpawnActor<AWeaponActor>(ScabbardToSpawn, scabbardST);
	FTransform bowST = GetMesh()->GetSocketTransform(BowBackTargetSocketName);
	BowActor = GetWorld()->SpawnActor<AWeaponActor>(BowToSpawn, bowST);
	FTransform arrowST = GetMesh()->GetSocketTransform(ArrowSocketName);
	ArrowActor = GetWorld()->SpawnActor<AWeaponActor>(ArrowToSpawn, arrowST);

	KatanaActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, KatanaSocketName);
	ScabbardActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale,
	                                 ScabbardSocketName);
	BowActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, BowBackTargetSocketName);
	ArrowActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, ArrowSocketName);

	ArrowActor->SetActorHiddenInGame(true);
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
