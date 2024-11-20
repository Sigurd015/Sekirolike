// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeaponActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ABaseWeaponActor::ABaseWeaponActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	WeaponCollisionBox->SetupAttachment(WeaponMesh);
	WeaponCollisionBox->SetBoxExtent(FVector(20.0f));
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SubMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SubMesh"));
	SubMesh->SetupAttachment(WeaponMesh);
}

void ABaseWeaponActor::AttachToSocket(USkeletalMeshComponent* Mesh, const FName& WeaponSocket,
                                      const FName& SubMeshSocket)
{
	WeaponMesh->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
	SubMesh->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetIncludingScale, SubMeshSocket);
	if (bHideSubMeshByDefault)
		SubMesh->SetVisibility(false);
}

void ABaseWeaponActor::EquipWeapon(USkeletalMeshComponent* Mesh, const FName& WeaponSocket)
{
	WeaponMesh->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
}
