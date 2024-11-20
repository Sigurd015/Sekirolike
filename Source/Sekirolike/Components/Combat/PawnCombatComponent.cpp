// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnCombatComponent.h"
#include "Sekirolike/Utils/Debug.h"
#include "Sekirolike/Weapon/BaseWeaponActor.h"

void UPawnCombatComponent::RegisterWeapon(const FGameplayTag& InWeaponTagToRegister,
                                          ABaseWeaponActor* InWeaponToRegister,
                                          bool bRegisterAsEquippedWeapon)
{
	checkf(!CharacterCarriedWeapons.Contains(InWeaponTagToRegister), TEXT("$s:Weapon already registered"),
	       *InWeaponTagToRegister.ToString());

	CharacterCarriedWeapons.Emplace(InWeaponTagToRegister, InWeaponToRegister);

	if (bRegisterAsEquippedWeapon)
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
}

ABaseWeaponActor* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTag)
{
	if (CharacterCarriedWeapons.Contains(InWeaponTag))
	{
		return *CharacterCarriedWeapons.Find(InWeaponTag);
	}

	return nullptr;
}

ABaseWeaponActor* UPawnCombatComponent::GetCurrentEquippedWeapon()
{
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}

	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}
