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

	MappedDright = Dright * FMath::Sqrt(1.0f - 0.5f * (Dup * Dup));
	MappedDup = Dup * FMath::Sqrt(1.0f - 0.5f * (Dright * Dright));
}
