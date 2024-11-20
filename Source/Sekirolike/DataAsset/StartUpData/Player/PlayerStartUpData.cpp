// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStartUpData.h"
#include "Sekirolike/AbilitySystem/BaseAbilitySystemComponent.h"
#include "Sekirolike/AbilitySystem/Abilities/BaseGameplayAbility.h"

bool FPlayerAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}

void UPlayerStartUpData::GiveToAbilitySystemComponent(class UBaseAbilitySystemComponent* InBaseASCToGive,
                                                      int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InBaseASCToGive, ApplyLevel);

	for (const FPlayerAbilitySet& AbilitySet : PlayerAbilitySets)
	{
		if (!AbilitySet.IsValid()) continue;


		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.SourceObject = InBaseASCToGive->GetAvatarActor();
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		InBaseASCToGive->GiveAbility(AbilitySpec);
	}
}
