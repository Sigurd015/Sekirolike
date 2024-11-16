// Fill out your copyright notice in the Description page of Project Settings.


#include "InputConfig.h"

UInputAction* UInputConfig::GetNativeInputActionByTag(const FGameplayTag& InputTag) const
{ 
	for (const FInputActionConfig& InputActionConfig : NativeInputActions)
	{
		if (InputActionConfig.InputTag == InputTag && InputActionConfig.InputAction)
		{
			return InputActionConfig.InputAction;
		}
	}
	return nullptr;
}
