// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class AWeaponActor;
class UAnimMontage;

UCLASS()
class SEKIROLIKE_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
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
	AWeaponActor* KatanaActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Mesh|Weapon Actor", meta = (AllowPrivateAccess = "true"))
	AWeaponActor* ScabbardActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Mesh|Weapon Actor", meta = (AllowPrivateAccess = "true"))
	AWeaponActor* BowActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Mesh|Weapon Actor", meta = (AllowPrivateAccess = "true"))
	AWeaponActor* ArrowActor;

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

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
