// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Sekirolike/Weapon/WeaponActor.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	FTransform bowST = GetMesh()->GetSocketTransform(BowBackTargetSocketName);
	BowActor = GetWorld()->SpawnActor<AWeaponActor>(BowToSpawn, bowST);
	FTransform arrowST = GetMesh()->GetSocketTransform(ArrowSocketName);
	ArrowActor = GetWorld()->SpawnActor<AWeaponActor>(ArrowToSpawn, arrowST);

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
