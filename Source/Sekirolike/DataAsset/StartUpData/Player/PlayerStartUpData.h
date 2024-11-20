// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Sekirolike/DataAsset/StartUpData/StartUpData.h"
#include "PlayerStartUpData.generated.h"

class UBaseGameplayAbility;

USTRUCT(BlueprintType)
struct FPlayerAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Categories="InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UBaseGameplayAbility> AbilityToGrant;

	bool IsValid() const;
};

UCLASS()
class SEKIROLIKE_API UPlayerStartUpData : public UStartUpData
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(class UBaseAbilitySystemComponent* InBaseASCToGive,
	                                          int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="StartUpData", meta=(TitleProperty="InputTag"))
	TArray<FPlayerAbilitySet> PlayerAbilitySets;
};
