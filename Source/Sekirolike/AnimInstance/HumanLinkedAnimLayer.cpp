// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanLinkedAnimLayer.h"
#include "HumanAnimInstance.h"

UHumanAnimInstance* UHumanLinkedAnimLayer::GetHumanAnimInstance() const
{
	return Cast<UHumanAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
