// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAnimInstance.h"
#include "HumanLinkedAnimLayer.generated.h"

class UHumanAnimInstance;
/**
 * 
 */
UCLASS()
class SEKIROLIKE_API UHumanLinkedAnimLayer : public UBaseAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	UHumanAnimInstance* GetHumanAnimInstance() const;
};
