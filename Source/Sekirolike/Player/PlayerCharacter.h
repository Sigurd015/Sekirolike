// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
struct FInputActionInstance;
struct FEnhancedInputActionValueBinding;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SEKIROLIKE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	FEnhancedInputActionValueBinding* MoveActionBinding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	FEnhancedInputActionValueBinding* LookActionBinding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Camera Settings")
	float CameraMaxEulerX = 30.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Camera Settings")
	float CameraMinEulerX = -40.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Camera Settings")
	float CameraHorizontalSpeed = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Camera Settings")
	float CameraVerticalSpeed = 50.0f;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Signals|Animation", meta = (AllowPrivateAccess = "true"))
	bool Dodge;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Signals|Animation", meta = (AllowPrivateAccess = "true"))
	float Forward;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Signals|Animation", meta = (AllowPrivateAccess = "true"))
	float Right;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Signals", meta = (AllowPrivateAccess = "true"))
	bool Sprint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Signals", meta = (AllowPrivateAccess = "true"))
	bool LockOn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera lock state", meta = (AllowPrivateAccess = "true"))
	bool LockState = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	FVector PlanarVec;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float Dmag;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	FVector Dvec;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera lock state", meta = (AllowPrivateAccess = "true"))
	bool LockPlanar = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void StartSprint(const FInputActionInstance& instance);
	void OnSprint(const FInputActionInstance& instance);
	void StopSprinting(const FInputActionInstance& instance);

	void GridMapping(float deltaTime);
	void Locomotion(float deltaTime);
	void CameraControl(float deltaTime);
};