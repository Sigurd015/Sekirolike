// Fill out your copyright notice in the Description page of Project Settings.


#include "StartUpData.h"
#include "Sekirolike/AbilitySystem/BaseAbilitySystemComponent.h"
#include "Sekirolike/AbilitySystem/Abilities/BaseGameplayAbility.h"

void UStartUpData::GiveToAbilitySystemComponent(class UBaseAbilitySystemComponent* InBaseASCToGive, int32 ApplyLevel)
{
	check(InBaseASCToGive);

	GrantAbilities(ActivateOnGivenAbilities, InBaseASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InBaseASCToGive, ApplyLevel);
}

void UStartUpData::GrantAbilities(const TArray<TSubclassOf<UBaseGameplayAbility>>& InAbilitiesToGive,
                                  class UBaseAbilitySystemComponent* InBaseASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())
		return;

	for (const TSubclassOf<UBaseGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability)
			continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.SourceObject = InBaseASCToGive->GetAvatarActor();

		InBaseASCToGive->GiveAbility(AbilitySpec);
	}
}
