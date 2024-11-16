// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanAnimInstance.h"
#include "Sekirolike/Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UHumanAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ABaseCharacter>(TryGetPawnOwner());
	if (Character)
	{
		MovementComponent = Character->GetCharacterMovement();
	}
}

void UHumanAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (!Character || !MovementComponent)
		return;

	GroundSpeed = Character->GetVelocity().Size2D();
	bHasAcceleration = MovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.0f;
}
