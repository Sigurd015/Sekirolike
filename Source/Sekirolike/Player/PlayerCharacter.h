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
class AActor;
class UAnimInstance;


UCLASS()
class SEKIROLIKE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
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
	UInputAction* SprintDodgeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LockAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimInstance* AnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Camera Settings")
	float CameraMaxEulerX = 30.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Camera Settings")
	float CameraMinEulerX = -40.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Camera Settings")
	float CameraHorizontalSpeed = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Camera Settings")
	float CameraVerticalSpeed = 50.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Camera Settings|Lock Target")
	float LockTargetHeightOffset = 15.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Camera Settings|Lock Target")
	float LockTargetDistance = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Camera Settings|Lock Target")
	float LockTargetRadius = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Montage|Dodge",
		meta = (AllowPrivateAccess = "true"))
	UAnimMontage* DodgeForwardAnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Montage|Dodge",
		meta = (AllowPrivateAccess = "true"))
	UAnimMontage* DodgeBackwardAnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Montage|Dodge",
		meta = (AllowPrivateAccess = "true"))
	UAnimMontage* DodgeLeftAnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Montage|Dodge",
		meta = (AllowPrivateAccess = "true"))
	UAnimMontage* DodgeRightAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Montage|Attack",
		meta = (AllowPrivateAccess = "true"))
	UAnimMontage* Attack1AnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Montage|Attack",
		meta = (AllowPrivateAccess = "true"))
	UAnimMontage* Attack2AnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Montage|Attack",
		meta = (AllowPrivateAccess = "true"))
	UAnimMontage* Attack3AnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Montage|Attack",
		meta = (AllowPrivateAccess = "true"))
	UAnimMontage* Attack4AnimMontage;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Signals|Animation", meta = (AllowPrivateAccess = "true"))
	float Forward;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Signals|Animation", meta = (AllowPrivateAccess = "true"))
	float Right;

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
	void StartSprint(const FInputActionInstance& instance);
	void StopSprinting(const FInputActionInstance& instance);
	void Dodge(const FInputActionInstance& instance);
	void Attack(const FInputActionInstance& instance);

	void LockUnlock();

	void GridMapping();
	void Locomotion(float deltaTime);
	void CameraControl(float deltaTime);
};
