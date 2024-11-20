// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sekirolike/CustomTypes/CustomStructTypes.h"
#include "BaseWeaponActor.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class SEKIROLIKE_API ABaseWeaponActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseWeaponActor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<UBoxComponent> WeaponCollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<UStaticMeshComponent> SubMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	bool bHideSubMeshByDefault = false;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|AnimLayer")
	FWeaponData WeaponData;
	
	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return WeaponCollisionBox; }

	UFUNCTION(BlueprintCallable, Category = "Weapon|Setup")
	void AttachToSocket(USkeletalMeshComponent* Mesh, const FName& WeaponSocket, const FName& SubMeshSocket);

	UFUNCTION(BlueprintCallable, Category = "Weapon|Equip")
	void EquipWeapon(USkeletalMeshComponent* Mesh, const FName& WeaponSocket);
};
