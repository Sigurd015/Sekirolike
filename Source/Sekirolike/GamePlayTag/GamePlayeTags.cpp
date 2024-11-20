// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayeTags.h"

namespace GamePlayTags
{
	/** InputTag **/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Sprint_Doge, "InputTag.Sprint_Doge");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack, "InputTag.Attack");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable, "InputTag.Toggleable");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable_TargetLock, "InputTag.Toggleable.TargetLock");

	/** AbilityTag **/
	UE_DEFINE_GAMEPLAY_TAG(AbilityTag_TargetLock, "AbilityTag.TargetLock");

	/** StateTag **/
	UE_DEFINE_GAMEPLAY_TAG(StateTag_TargetLock, "StateTag.TargetLock");
	
	/** WeaponTag **/
	UE_DEFINE_GAMEPLAY_TAG(WeaponTag_Katana, "WeaponTag.Katana");
	UE_DEFINE_GAMEPLAY_TAG(WeaponTag_Bow, "WeaponTag.Bow");

	/** EventTag **/
	UE_DEFINE_GAMEPLAY_TAG(EventTag_EquipWeapon_Katana, "EventTag.EquipWeapon.Katana");
}
