// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "Sekirolike/AbilitySystem/BaseAbilitySystemComponent.h"
#include "Sekirolike/Character/BaseCharacter.h"

void UBaseGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (AbilityActivationPolicy == EAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
	}
}

void UBaseGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo,
                                      const FGameplayAbilityActivationInfo ActivationInfo,
                                      bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy == EAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
	}
}

ABaseCharacter* UBaseGameplayAbility::GetBaseCharacterFromActorInfo()
{
	if (!CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter = Cast<ABaseCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedBaseCharacter.IsValid() ? CachedBaseCharacter.Get() : nullptr;
}

UPawnCombatComponent* UBaseGameplayAbility::GetPawnCombatComponentFromActorInfo()
{
	return GetBaseCharacterFromActorInfo()->GetPawnCombatComponent();
}

UBaseAbilitySystemComponent* UBaseGameplayAbility::GetBaseAbilitySystemComponentFromActorInfo() const
{
	return Cast<UBaseAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}
