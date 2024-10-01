// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerInputManager.h"
#include "Components/SkeletalMeshComponent.h"

// Elliptical Grid Mapping
// See: https://arxiv.org/ftp/arxiv/papers/1509/1509.06344.pdf
void APlayerInputManager::CalLeftStickInput(FVector2D axis, float deltaTime, float interpSpeed)
{
	float targetDup = axis.Y;
	float targetDright = axis.X;
	Dup = FMath::FInterpTo(Dup, targetDup, deltaTime, interpSpeed);
	Dright = FMath::FInterpTo(Dright, targetDright, deltaTime, interpSpeed);

	FVector2f temp = FVector2f::ZeroVector;
	temp.X = Dright * FMath::Sqrt(1.0f - 0.5f * (Dup * Dup));
	temp.Y = Dup * FMath::Sqrt(1.0f - 0.5f * (Dright * Dright));

	Dmag = FMath::Sqrt(temp.X * temp.X + temp.Y * temp.Y);

	FRotator rotator = PlayerTarget->GetControlRotation();
	FRotator yawRotator = FRotator(0, rotator.Yaw, 0);
	FVector forward = FQuat(yawRotator).GetForwardVector();
	FVector right = FQuat(yawRotator).GetRightVector();

	Dvec = temp.X * right + temp.Y * forward;
}
