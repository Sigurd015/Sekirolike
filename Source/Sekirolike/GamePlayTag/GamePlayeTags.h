// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace GamePlayTags
{
	/** InputTag **/
	SEKIROLIKE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	SEKIROLIKE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	SEKIROLIKE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Sprint_Doge);
	SEKIROLIKE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Jump);
	SEKIROLIKE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Attack);
	SEKIROLIKE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable)
	SEKIROLIKE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable_TargetLock);

	/** AbilityTag **/
	SEKIROLIKE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AbilityTag_TargetLock);

	/** StateTag **/
	SEKIROLIKE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(StateTag_TargetLock);

	/** WeaponTag **/
	SEKIROLIKE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(WeaponTag_Katana);
	SEKIROLIKE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(WeaponTag_Bow);

	/** EventTag **/
	SEKIROLIKE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(EventTag_EquipWeapon_Katana);
}
