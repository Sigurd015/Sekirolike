// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnCombatComponent.h"
#include "PlayerCombatComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SEKIROLIKE_API UPlayerCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
};
