// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAbilitySystemComponent.h"
#include "Sekirolike/GamePlayTag/GamePlayeTags.h"

void UBaseAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
		return;

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag)) continue;
		{
			if (InInputTag.MatchesTag(GamePlayTags::InputTag_Toggleable))
				CancelAbilityHandle(AbilitySpec.Handle);
			else
				TryActivateAbility(AbilitySpec.Handle);

			TryActivateAbility(AbilitySpec.Handle);
		}
	}
}

void UBaseAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
}
