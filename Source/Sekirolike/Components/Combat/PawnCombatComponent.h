// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Sekirolike/Components/PawnExtensionComponentBase.h"
#include "PawnCombatComponent.generated.h"

class ABaseWeaponActor;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SEKIROLIKE_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category="CombatComponent")
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION(BlueprintCallable, Category="CombatComponent")
	void RegisterWeapon(const FGameplayTag& InWeaponTagToRegister, ABaseWeaponActor* InWeaponToRegister,
	                    bool bRegisterAsEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category="CombatComponent")
	ABaseWeaponActor* GetCharacterCarriedWeaponByTag(const FGameplayTag& InWeaponTag);

	UFUNCTION(BlueprintCallable, Category="CombatComponent")
	ABaseWeaponActor* GetCurrentEquippedWeapon();

private:
	TMap<FGameplayTag, ABaseWeaponActor*> CharacterCarriedWeapons;
};
