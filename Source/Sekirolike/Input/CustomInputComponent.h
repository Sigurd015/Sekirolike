// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Sekirolike/DataAsset/Input/InputConfig.h"
#include "CustomInputComponent.generated.h"

UCLASS()
class SEKIROLIKE_API UCustomInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template <class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UInputConfig* InInputConfig, const FGameplayTag& InInputTag,
	                           ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Callback)
	{
		checkf(InInputConfig, TEXT("InputConfig is nullptr"));

		if (UInputAction* InputAction = InInputConfig->GetNativeInputActionByTag(InInputTag))
		{
			BindAction(InputAction, TriggerEvent, ContextObject, Callback);
		}
	}

	template <class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UInputConfig* InInputConfig, UserObject* ContextObject,
	                            CallbackFunc PressedFunc, CallbackFunc RelasedFunc)
	{
		checkf(InInputConfig, TEXT("InputConfig is nullptr"));

		for (const FInputActionConfig& AbilityInputActionConfig : InInputConfig->AbilityInputActions)
		{
			if (!AbilityInputActionConfig.IsValid()) continue;

			BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, ContextObject, PressedFunc,
			           AbilityInputActionConfig.InputTag);
			BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, RelasedFunc,
			           AbilityInputActionConfig.InputTag);
		}
	}
};
