// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class SEKIROLIKE_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Anim Signals")
	float Forward;
	UPROPERTY(BlueprintReadWrite, Category = "Anim Signals")
	float Right;
	UPROPERTY(BlueprintReadWrite, Category = "Anim Signals")
	bool IsGround;
	UPROPERTY(BlueprintReadWrite, Category = "Anim Signals")
	bool Jump;
};
