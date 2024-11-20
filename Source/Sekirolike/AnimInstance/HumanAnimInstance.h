// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAnimInstance.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimInstance.h"
#include "HumanAnimInstance.generated.h"

class ABaseCharacter;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class SEKIROLIKE_API UHumanAnimInstance : public UBaseAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Owner")
	TObjectPtr<ABaseCharacter> Character;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Owner")
	TObjectPtr<UCharacterMovementComponent> MovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Signals|Locomotion")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Signals|Locomotion")
	bool bHasAcceleration;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Signals|Locomotion")
	float Direction;
};
