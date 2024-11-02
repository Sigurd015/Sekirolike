// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharacter.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Character = Cast<APlayerCharacter>(TryGetPawnOwner());
	if (Character)
	{
		MovementComponent = Character->GetCharacterMovement();
	}
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (Character)
	{
		Forward = FMath::FInterpTo(Forward, Character->Forward, DeltaSeconds, 5.0f);
		Right = Character->Right;
		IsFalling = MovementComponent->IsFalling();
		Velocity = Character->GetVelocity();
	}
}
