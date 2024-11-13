// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UAnimInstance;
class AWeaponActor;
class UAnimMontage;

UCLASS()
class SEKIROLIKE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimInstance> AnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh|Socket", meta = (AllowPrivateAccess = "true"))
	FName KatanaSocketName = "katana_r";
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh|Socket", meta = (AllowPrivateAccess = "true"))
	FName ScabbardSocketName = "Scabbard_Target01";
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh|Socket", meta = (AllowPrivateAccess = "true"))
	FName BowSocketName = "bow";
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh|Socket", meta = (AllowPrivateAccess = "true"))
	FName BowBackTargetSocketName = "Bow_BackTarget";
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh|Socket", meta = (AllowPrivateAccess = "true"))
	FName ArrowSocketName = "arrow";

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Mesh|Weapon Class", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeaponActor> KatanaToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Mesh|Weapon Class", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeaponActor> ScabbardToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Mesh|Weapon Class", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeaponActor> BowToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Mesh|Weapon Class", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeaponActor> ArrowToSpawn;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Mesh|Weapon Actor", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AWeaponActor> KatanaActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Mesh|Weapon Actor", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AWeaponActor> ScabbardActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Mesh|Weapon Actor", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AWeaponActor> BowActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Mesh|Weapon Actor", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AWeaponActor> ArrowActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Montage|Dodge",
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> DodgeForwardAnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Montage|Dodge",
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> DodgeBackwardAnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Montage|Dodge",
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> DodgeLeftAnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Montage|Dodge",
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> DodgeRightAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Montage|Attack",
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> Attack1AnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Montage|Attack",
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> Attack2AnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Montage|Attack",
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> Attack3AnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Montage|Attack",
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> Attack4AnimMontage;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Signals|Animation", meta = (AllowPrivateAccess = "true"))
	float Forward;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Signals|Animation", meta = (AllowPrivateAccess = "true"))
	float Right;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Signals|Animation", meta = (AllowPrivateAccess = "true"))
	bool Defense;

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
