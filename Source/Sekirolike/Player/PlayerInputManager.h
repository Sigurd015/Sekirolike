// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerInputManager.generated.h"

UCLASS()
class SEKIROLIKE_API APlayerInputManager : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Output Signals")
	float Dup;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Output Signals")
	float Dright;
	// Elliptical grid mapped dup
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Output Signals")
	float MappedDup;
	// Elliptical grid mapped dright
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Output Signals")
	float MappedDright;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Output Signals")
	float Jup;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Output Signals")
	float Jright;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Output Signals")
	bool Dodge;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Output Signals")
	bool Sprint;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Output Signals")
	bool Jump;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Output Signals")
	bool LockOn;

protected:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void CalLeftStickInput(FVector2D axis, float deltaTime, float interpSpeed = 5.0f);
};
