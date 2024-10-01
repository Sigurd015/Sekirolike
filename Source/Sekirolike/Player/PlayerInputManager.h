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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Output Signals")
	float Dmag;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Output Signals")
	FVector Dvec;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Output Signals")
	float Jup;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Output Signals")
	float Jright;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Output Signals")
	bool Run;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Output Signals")
	bool Jump;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Output Signals")
	bool LockState;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AController> PlayerTarget;

protected:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void CalLeftStickInput(FVector2D axis, float deltaTime, float interpSpeed = 5.0f);
};
