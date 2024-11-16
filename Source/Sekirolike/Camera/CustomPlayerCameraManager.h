// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "CustomPlayerCameraManager.generated.h"

UCLASS()
class SEKIROLIKE_API ACustomPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	ACustomPlayerCameraManager();
};
