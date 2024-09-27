// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CalInputValue.generated.h"

/**
 *
 */
UCLASS()
class SEKIROLIKE_API UCalInputValue : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category = "Input")
	static void CalLeftStickValue(FVector2f axis, FVector3f forward, FVector3f right,
		float& dup, float& dright, float& dmag, FVector3f& dvec, float deltaTime, float interpSpeed = 5.0f);
};
