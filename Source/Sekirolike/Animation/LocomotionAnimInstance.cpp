// Fill out your copyright notice in the Description page of Project Settings.


#include "LocomotionAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Sekirolike/Character/BaseCharacter.h"

void ULocomotionAnimInstance::NativeInitializeAnimation()
{
	Character = Cast<ABaseCharacter>(TryGetPawnOwner());
	if (Character)
	{
		MovementComponent = Character->GetCharacterMovement();
	}
}

void ULocomotionAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (Character)
	{
		Forward = Character->Forward;
		Right = Character->Right;
		IsFalling = MovementComponent->IsFalling();
		Velocity = Character->GetVelocity();
		Defense = Character->Defense;
	}
}
