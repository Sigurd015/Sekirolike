// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class SEKIROLIKE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
	TObjectPtr<class APlayerInputManager> PlayerInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
	TObjectPtr<class UPlayerAnimInstance> Animator;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera lock state")
	bool LockState = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
	float CameraMaxEulerX = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
	float CameraMinEulerX = -40.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
	float CameraHorizontalSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
	float CameraVerticalSpeed = 50.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector PlanarVec;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	float Dmag;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector Dvec;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Character Movement")
	void Locomotion(float deltaTime);

	UFUNCTION(BlueprintCallable, Category = "Camera Movement")
	void CameraControl(float deltaTime);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
