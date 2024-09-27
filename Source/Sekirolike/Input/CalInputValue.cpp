// Fill out your copyright notice in the Description page of Project Settings.


#include "CalInputValue.h"

// Elliptical Grid Mapping
// See: https://arxiv.org/ftp/arxiv/papers/1509/1509.06344.pdf
void UCalInputValue::CalLeftStickValue(FVector2f axis, FVector3f forward, FVector3f right,
	float& dup, float& dright, float& dmag, FVector3f& dvec, float deltaTime, float interpSpeed)
{
	float targetDup = axis.Y;
	float targetDright = axis.X;
	dup = FMath::FInterpTo(dup, targetDup, deltaTime, interpSpeed);
	dright = FMath::FInterpTo(dright, targetDright, deltaTime, interpSpeed);

	FVector2f temp = FVector2f::ZeroVector;
	temp.X = dright * FMath::Sqrt(1.0f - 0.5f * (dup * dup));
	temp.Y = dup * FMath::Sqrt(1.0f - 0.5f * (dright * dright));

	dmag = FMath::Sqrt(temp.X * temp.X + temp.Y * temp.Y);
	dvec = temp.X * right + temp.Y * forward;
}