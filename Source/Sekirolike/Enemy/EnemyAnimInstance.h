// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

class AEnemyCharacter;
class UCharacterMovementComponent;

UCLASS()
class SEKIROLIKE_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ref|Player", meta = (AllowPrivateAccess = "true"))
	AEnemyCharacter* Character;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ref|Player", meta = (AllowPrivateAccess = "true"))
	UCharacterMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Signals|Animation", meta = (AllowPrivateAccess = "true"))
	bool IsFalling;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Signals|Animation", meta = (AllowPrivateAccess = "true"))
	float Forward;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Signals|Animation", meta = (AllowPrivateAccess = "true"))
	float Right;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Signals|Animation", meta = (AllowPrivateAccess = "true"))
	FVector Velocity;

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
