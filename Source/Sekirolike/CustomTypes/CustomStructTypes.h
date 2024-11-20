// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CustomStructTypes.generated.h"

class UHumanLinkedAnimLayer;

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UHumanLinkedAnimLayer> WeaponAnimLayerToLink;
};
