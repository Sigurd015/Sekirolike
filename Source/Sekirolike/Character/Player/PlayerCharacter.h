// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sekirolike/Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionInstance;
struct FEnhancedInputActionValueBinding;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SEKIROLIKE_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;
	TObjectPtr<FEnhancedInputActionValueBinding> MoveActionBinding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;
	TObjectPtr<FEnhancedInputActionValueBinding> LookActionBinding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SprintDodgeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LockAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> AttackAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> DefenseDeflectAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera|Camera Settings")
	float CameraMaxEulerX = 30.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera|Camera Settings")
	float CameraMinEulerX = -40.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera|Camera Settings")
	float CameraHorizontalSpeed = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera|Camera Settings")
	float CameraVerticalSpeed = 50.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera|Camera Settings|Lock Target")
	float LockTargetHeightOffset = 15.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera|Camera Settings|Lock Target")
	float LockTargetDistance = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera|Camera Settings|Lock Target")
	float LockTargetRadius = 50.0f;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Signals", meta = (AllowPrivateAccess = "true"))
	bool Sprint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Signals|Camera", meta = (AllowPrivateAccess = "true"))
	bool LockState = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Signals|Camera", meta = (AllowPrivateAccess = "true"))
	AActor* Target;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Signals|Camera", meta = (AllowPrivateAccess = "true"))
	float TargetHeight = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Signals|Movement", meta = (AllowPrivateAccess = "true"))
	FVector PlanarVec;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Signals|Movement", meta = (AllowPrivateAccess = "true"))
	float Dmag;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Signals|Movement", meta = (AllowPrivateAccess = "true"))
	FVector Dvec;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Signals|Movement", meta = (AllowPrivateAccess = "true"))
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
	void LockUnlock();
	void StartSprint(const FInputActionInstance& instance);
	void StopSprinting(const FInputActionInstance& instance);
	void Dodge(const FInputActionInstance& instance);
	void Attack(const FInputActionInstance& instance);
	void StartDefense(const FInputActionInstance& instance);
	void StopDefending(const FInputActionInstance& instance);
	void Deflect(const FInputActionInstance& instance);

	void GridMapping();
	void Locomotion(float deltaTime);
	void CameraControl(float deltaTime);
};
