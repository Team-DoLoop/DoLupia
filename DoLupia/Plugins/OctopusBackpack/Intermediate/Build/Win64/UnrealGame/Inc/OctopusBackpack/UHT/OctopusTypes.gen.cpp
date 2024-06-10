// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "OctopusBackpack/Public/OctopusTypes.h"
#include "Runtime/Engine/Classes/Engine/HitResult.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeOctopusTypes() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FTransform();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UArrowComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UInstancedStaticMeshComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UPhysicsConstraintComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USkeletalMeshComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USphereComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USplineComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USplineMeshComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FHitResult();
OCTOPUSBACKPACK_API UClass* Z_Construct_UClass_UOctopusBackpackComponent_NoRegister();
OCTOPUSBACKPACK_API UEnum* Z_Construct_UEnum_OctopusBackpack_EOcto_Hand();
OCTOPUSBACKPACK_API UEnum* Z_Construct_UEnum_OctopusBackpack_EOcto_HandPoint();
OCTOPUSBACKPACK_API UEnum* Z_Construct_UEnum_OctopusBackpack_EOcto_Move();
OCTOPUSBACKPACK_API UEnum* Z_Construct_UEnum_OctopusBackpack_EOctoHandAction();
OCTOPUSBACKPACK_API UScriptStruct* Z_Construct_UScriptStruct_FOctoHandStatus();
OCTOPUSBACKPACK_API UScriptStruct* Z_Construct_UScriptStruct_FOctoTentaclesStruct();
UPackage* Z_Construct_UPackage__Script_OctopusBackpack();
// End Cross Module References

// Begin Enum EOcto_Move
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EOcto_Move;
static UEnum* EOcto_Move_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EOcto_Move.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EOcto_Move.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_OctopusBackpack_EOcto_Move, (UObject*)Z_Construct_UPackage__Script_OctopusBackpack(), TEXT("EOcto_Move"));
	}
	return Z_Registration_Info_UEnum_EOcto_Move.OuterSingleton;
}
template<> OCTOPUSBACKPACK_API UEnum* StaticEnum<EOcto_Move>()
{
	return EOcto_Move_StaticEnum();
}
struct Z_Construct_UEnum_OctopusBackpack_EOcto_Move_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BACKWARD.DisplayName", "Backward" },
		{ "BACKWARD.Name", "EOcto_Move::BACKWARD" },
		{ "BlueprintType", "true" },
		{ "BOTTOM.DisplayName", "Bottom" },
		{ "BOTTOM.Name", "EOcto_Move::BOTTOM" },
		{ "FORWARD.DisplayName", "Forward" },
		{ "FORWARD.Name", "EOcto_Move::FORWARD" },
		{ "LEFT.DisplayName", "Left" },
		{ "LEFT.Name", "EOcto_Move::LEFT" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
		{ "NONE.DisplayName", "None" },
		{ "NONE.Name", "EOcto_Move::NONE" },
		{ "RIGHT.DisplayName", "Right" },
		{ "RIGHT.Name", "EOcto_Move::RIGHT" },
		{ "TOP.DisplayName", "Top" },
		{ "TOP.Name", "EOcto_Move::TOP" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EOcto_Move::NONE", (int64)EOcto_Move::NONE },
		{ "EOcto_Move::FORWARD", (int64)EOcto_Move::FORWARD },
		{ "EOcto_Move::BACKWARD", (int64)EOcto_Move::BACKWARD },
		{ "EOcto_Move::TOP", (int64)EOcto_Move::TOP },
		{ "EOcto_Move::BOTTOM", (int64)EOcto_Move::BOTTOM },
		{ "EOcto_Move::LEFT", (int64)EOcto_Move::LEFT },
		{ "EOcto_Move::RIGHT", (int64)EOcto_Move::RIGHT },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_OctopusBackpack_EOcto_Move_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_OctopusBackpack,
	nullptr,
	"EOcto_Move",
	"EOcto_Move",
	Z_Construct_UEnum_OctopusBackpack_EOcto_Move_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_OctopusBackpack_EOcto_Move_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_OctopusBackpack_EOcto_Move_Statics::Enum_MetaDataParams), Z_Construct_UEnum_OctopusBackpack_EOcto_Move_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_OctopusBackpack_EOcto_Move()
{
	if (!Z_Registration_Info_UEnum_EOcto_Move.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EOcto_Move.InnerSingleton, Z_Construct_UEnum_OctopusBackpack_EOcto_Move_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EOcto_Move.InnerSingleton;
}
// End Enum EOcto_Move

// Begin Enum EOctoHandAction
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EOctoHandAction;
static UEnum* EOctoHandAction_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EOctoHandAction.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EOctoHandAction.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_OctopusBackpack_EOctoHandAction, (UObject*)Z_Construct_UPackage__Script_OctopusBackpack(), TEXT("EOctoHandAction"));
	}
	return Z_Registration_Info_UEnum_EOctoHandAction.OuterSingleton;
}
template<> OCTOPUSBACKPACK_API UEnum* StaticEnum<EOctoHandAction>()
{
	return EOctoHandAction_StaticEnum();
}
struct Z_Construct_UEnum_OctopusBackpack_EOctoHandAction_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "ATTACHED.DisplayName", "Attached" },
		{ "ATTACHED.Name", "EOctoHandAction::ATTACHED" },
		{ "ATTACKS.DisplayName", "Attacks the target" },
		{ "ATTACKS.Name", "EOctoHandAction::ATTACKS" },
		{ "BlueprintType", "true" },
		{ "FALLING.DisplayName", "Falling" },
		{ "FALLING.Name", "EOctoHandAction::FALLING" },
		{ "GRABBED.DisplayName", "Grabbed the target" },
		{ "GRABBED.Name", "EOctoHandAction::GRABBED" },
		{ "GRABBED_RETURN.DisplayName", "Grabbed the target and return" },
		{ "GRABBED_RETURN.Name", "EOctoHandAction::GRABBED_RETURN" },
		{ "IDLE.DisplayName", "Idle" },
		{ "IDLE.Name", "EOctoHandAction::IDLE" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
		{ "MOVE_TO_ATTACH_POINT.DisplayName", "Moves towards the attachment point" },
		{ "MOVE_TO_ATTACH_POINT.Name", "EOctoHandAction::MOVE_TO_ATTACH_POINT" },
		{ "RETURNS.DisplayName", "Returns to its place" },
		{ "RETURNS.Name", "EOctoHandAction::RETURNS" },
		{ "SHOW_HIDE.DisplayName", "Show Hide" },
		{ "SHOW_HIDE.Name", "EOctoHandAction::SHOW_HIDE" },
		{ "THROW.DisplayName", "Throw the object" },
		{ "THROW.Name", "EOctoHandAction::THROW" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EOctoHandAction::IDLE", (int64)EOctoHandAction::IDLE },
		{ "EOctoHandAction::MOVE_TO_ATTACH_POINT", (int64)EOctoHandAction::MOVE_TO_ATTACH_POINT },
		{ "EOctoHandAction::ATTACHED", (int64)EOctoHandAction::ATTACHED },
		{ "EOctoHandAction::GRABBED_RETURN", (int64)EOctoHandAction::GRABBED_RETURN },
		{ "EOctoHandAction::ATTACKS", (int64)EOctoHandAction::ATTACKS },
		{ "EOctoHandAction::RETURNS", (int64)EOctoHandAction::RETURNS },
		{ "EOctoHandAction::GRABBED", (int64)EOctoHandAction::GRABBED },
		{ "EOctoHandAction::THROW", (int64)EOctoHandAction::THROW },
		{ "EOctoHandAction::FALLING", (int64)EOctoHandAction::FALLING },
		{ "EOctoHandAction::SHOW_HIDE", (int64)EOctoHandAction::SHOW_HIDE },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_OctopusBackpack_EOctoHandAction_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_OctopusBackpack,
	nullptr,
	"EOctoHandAction",
	"EOctoHandAction",
	Z_Construct_UEnum_OctopusBackpack_EOctoHandAction_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_OctopusBackpack_EOctoHandAction_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_OctopusBackpack_EOctoHandAction_Statics::Enum_MetaDataParams), Z_Construct_UEnum_OctopusBackpack_EOctoHandAction_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_OctopusBackpack_EOctoHandAction()
{
	if (!Z_Registration_Info_UEnum_EOctoHandAction.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EOctoHandAction.InnerSingleton, Z_Construct_UEnum_OctopusBackpack_EOctoHandAction_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EOctoHandAction.InnerSingleton;
}
// End Enum EOctoHandAction

// Begin Enum EOcto_Hand
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EOcto_Hand;
static UEnum* EOcto_Hand_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EOcto_Hand.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EOcto_Hand.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_OctopusBackpack_EOcto_Hand, (UObject*)Z_Construct_UPackage__Script_OctopusBackpack(), TEXT("EOcto_Hand"));
	}
	return Z_Registration_Info_UEnum_EOcto_Hand.OuterSingleton;
}
template<> OCTOPUSBACKPACK_API UEnum* StaticEnum<EOcto_Hand>()
{
	return EOcto_Hand_StaticEnum();
}
struct Z_Construct_UEnum_OctopusBackpack_EOcto_Hand_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "LEFT_BOTTOM.DisplayName", "LeftBottom" },
		{ "LEFT_BOTTOM.Name", "EOcto_Hand::LEFT_BOTTOM" },
		{ "LEFT_TOP.DisplayName", "LeftTop" },
		{ "LEFT_TOP.Name", "EOcto_Hand::LEFT_TOP" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
		{ "RIGHT_BOTTOM.DisplayName", "RightBottom" },
		{ "RIGHT_BOTTOM.Name", "EOcto_Hand::RIGHT_BOTTOM" },
		{ "RIGHT_TOP.DisplayName", "RightTop" },
		{ "RIGHT_TOP.Name", "EOcto_Hand::RIGHT_TOP" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EOcto_Hand::LEFT_BOTTOM", (int64)EOcto_Hand::LEFT_BOTTOM },
		{ "EOcto_Hand::RIGHT_BOTTOM", (int64)EOcto_Hand::RIGHT_BOTTOM },
		{ "EOcto_Hand::LEFT_TOP", (int64)EOcto_Hand::LEFT_TOP },
		{ "EOcto_Hand::RIGHT_TOP", (int64)EOcto_Hand::RIGHT_TOP },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_OctopusBackpack_EOcto_Hand_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_OctopusBackpack,
	nullptr,
	"EOcto_Hand",
	"EOcto_Hand",
	Z_Construct_UEnum_OctopusBackpack_EOcto_Hand_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_OctopusBackpack_EOcto_Hand_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_OctopusBackpack_EOcto_Hand_Statics::Enum_MetaDataParams), Z_Construct_UEnum_OctopusBackpack_EOcto_Hand_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_OctopusBackpack_EOcto_Hand()
{
	if (!Z_Registration_Info_UEnum_EOcto_Hand.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EOcto_Hand.InnerSingleton, Z_Construct_UEnum_OctopusBackpack_EOcto_Hand_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EOcto_Hand.InnerSingleton;
}
// End Enum EOcto_Hand

// Begin Enum EOcto_HandPoint
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EOcto_HandPoint;
static UEnum* EOcto_HandPoint_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EOcto_HandPoint.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EOcto_HandPoint.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_OctopusBackpack_EOcto_HandPoint, (UObject*)Z_Construct_UPackage__Script_OctopusBackpack(), TEXT("EOcto_HandPoint"));
	}
	return Z_Registration_Info_UEnum_EOcto_HandPoint.OuterSingleton;
}
template<> OCTOPUSBACKPACK_API UEnum* StaticEnum<EOcto_HandPoint>()
{
	return EOcto_HandPoint_StaticEnum();
}
struct Z_Construct_UEnum_OctopusBackpack_EOcto_HandPoint_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "FALLING_ORIGIN.DisplayName", "Falling" },
		{ "FALLING_ORIGIN.Name", "EOcto_HandPoint::FALLING_ORIGIN" },
		{ "FLY_GRAB_ORIGIN.DisplayName", "Fly Grab" },
		{ "FLY_GRAB_ORIGIN.Name", "EOcto_HandPoint::FLY_GRAB_ORIGIN" },
		{ "FLY_ORIGIN.DisplayName", "Fly" },
		{ "FLY_ORIGIN.Name", "EOcto_HandPoint::FLY_ORIGIN" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
		{ "WALK_GRAB_ORIGIN.DisplayName", "Wlak Grab" },
		{ "WALK_GRAB_ORIGIN.Name", "EOcto_HandPoint::WALK_GRAB_ORIGIN" },
		{ "WALK_ORIGIN.DisplayName", "Walk" },
		{ "WALK_ORIGIN.Name", "EOcto_HandPoint::WALK_ORIGIN" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EOcto_HandPoint::WALK_ORIGIN", (int64)EOcto_HandPoint::WALK_ORIGIN },
		{ "EOcto_HandPoint::WALK_GRAB_ORIGIN", (int64)EOcto_HandPoint::WALK_GRAB_ORIGIN },
		{ "EOcto_HandPoint::FLY_ORIGIN", (int64)EOcto_HandPoint::FLY_ORIGIN },
		{ "EOcto_HandPoint::FALLING_ORIGIN", (int64)EOcto_HandPoint::FALLING_ORIGIN },
		{ "EOcto_HandPoint::FLY_GRAB_ORIGIN", (int64)EOcto_HandPoint::FLY_GRAB_ORIGIN },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_OctopusBackpack_EOcto_HandPoint_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_OctopusBackpack,
	nullptr,
	"EOcto_HandPoint",
	"EOcto_HandPoint",
	Z_Construct_UEnum_OctopusBackpack_EOcto_HandPoint_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_OctopusBackpack_EOcto_HandPoint_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_OctopusBackpack_EOcto_HandPoint_Statics::Enum_MetaDataParams), Z_Construct_UEnum_OctopusBackpack_EOcto_HandPoint_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_OctopusBackpack_EOcto_HandPoint()
{
	if (!Z_Registration_Info_UEnum_EOcto_HandPoint.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EOcto_HandPoint.InnerSingleton, Z_Construct_UEnum_OctopusBackpack_EOcto_HandPoint_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EOcto_HandPoint.InnerSingleton;
}
// End Enum EOcto_HandPoint

// Begin ScriptStruct FOctoHandStatus
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_OctoHandStatus;
class UScriptStruct* FOctoHandStatus::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_OctoHandStatus.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_OctoHandStatus.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FOctoHandStatus, (UObject*)Z_Construct_UPackage__Script_OctopusBackpack(), TEXT("OctoHandStatus"));
	}
	return Z_Registration_Info_UScriptStruct_OctoHandStatus.OuterSingleton;
}
template<> OCTOPUSBACKPACK_API UScriptStruct* StaticStruct<FOctoHandStatus>()
{
	return FOctoHandStatus::StaticStruct();
}
struct Z_Construct_UScriptStruct_FOctoHandStatus_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_hand_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_handTransform_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_handBeforeMove_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_sizeHandNow_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_targetPoint_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_targetPointsArr_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_targetHitResult_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_checkPoint_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_action_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_timeAttached_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bBusyAlgo_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_walkMoveHandTime_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_walkRotateHandTime_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_throwImpulse_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bFinishAnimate_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_animRandRate_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_animTime_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_animIdleTime_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bCameraAnimation_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bLookInstance_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_grabbedObject_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_hand_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_hand;
	static const UECodeGen_Private::FStructPropertyParams NewProp_handTransform;
	static const UECodeGen_Private::FStructPropertyParams NewProp_handBeforeMove;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_sizeHandNow;
	static const UECodeGen_Private::FStructPropertyParams NewProp_targetPoint;
	static const UECodeGen_Private::FStructPropertyParams NewProp_targetPointsArr_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_targetPointsArr;
	static const UECodeGen_Private::FStructPropertyParams NewProp_targetHitResult;
	static const UECodeGen_Private::FStructPropertyParams NewProp_checkPoint;
	static const UECodeGen_Private::FBytePropertyParams NewProp_action_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_action;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_timeAttached;
	static void NewProp_bBusyAlgo_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bBusyAlgo;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_walkMoveHandTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_walkRotateHandTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_throwImpulse;
	static void NewProp_bFinishAnimate_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bFinishAnimate;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_animRandRate;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_animTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_animIdleTime;
	static void NewProp_bCameraAnimation_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bCameraAnimation;
	static void NewProp_bLookInstance_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bLookInstance;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_grabbedObject;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FOctoHandStatus>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_hand_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_hand = { "hand", nullptr, (EPropertyFlags)0x0010000000020815, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoHandStatus, hand), Z_Construct_UEnum_OctopusBackpack_EOcto_Hand, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_hand_MetaData), NewProp_hand_MetaData) }; // 1375996686
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_handTransform = { "handTransform", nullptr, (EPropertyFlags)0x0010000000020815, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoHandStatus, handTransform), Z_Construct_UScriptStruct_FTransform, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_handTransform_MetaData), NewProp_handTransform_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_handBeforeMove = { "handBeforeMove", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoHandStatus, handBeforeMove), Z_Construct_UScriptStruct_FTransform, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_handBeforeMove_MetaData), NewProp_handBeforeMove_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_sizeHandNow = { "sizeHandNow", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoHandStatus, sizeHandNow), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_sizeHandNow_MetaData), NewProp_sizeHandNow_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_targetPoint = { "targetPoint", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoHandStatus, targetPoint), Z_Construct_UScriptStruct_FTransform, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_targetPoint_MetaData), NewProp_targetPoint_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_targetPointsArr_Inner = { "targetPointsArr", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_targetPointsArr = { "targetPointsArr", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoHandStatus, targetPointsArr), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_targetPointsArr_MetaData), NewProp_targetPointsArr_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_targetHitResult = { "targetHitResult", nullptr, (EPropertyFlags)0x0010008000010001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoHandStatus, targetHitResult), Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_targetHitResult_MetaData), NewProp_targetHitResult_MetaData) }; // 4100991306
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_checkPoint = { "checkPoint", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoHandStatus, checkPoint), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_checkPoint_MetaData), NewProp_checkPoint_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_action_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_action = { "action", nullptr, (EPropertyFlags)0x0010000000020815, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoHandStatus, action), Z_Construct_UEnum_OctopusBackpack_EOctoHandAction, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_action_MetaData), NewProp_action_MetaData) }; // 2925050406
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_timeAttached = { "timeAttached", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoHandStatus, timeAttached), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_timeAttached_MetaData), NewProp_timeAttached_MetaData) };
void Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_bBusyAlgo_SetBit(void* Obj)
{
	((FOctoHandStatus*)Obj)->bBusyAlgo = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_bBusyAlgo = { "bBusyAlgo", nullptr, (EPropertyFlags)0x0010000000020815, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FOctoHandStatus), &Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_bBusyAlgo_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bBusyAlgo_MetaData), NewProp_bBusyAlgo_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_walkMoveHandTime = { "walkMoveHandTime", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoHandStatus, walkMoveHandTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_walkMoveHandTime_MetaData), NewProp_walkMoveHandTime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_walkRotateHandTime = { "walkRotateHandTime", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoHandStatus, walkRotateHandTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_walkRotateHandTime_MetaData), NewProp_walkRotateHandTime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_throwImpulse = { "throwImpulse", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoHandStatus, throwImpulse), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_throwImpulse_MetaData), NewProp_throwImpulse_MetaData) };
void Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_bFinishAnimate_SetBit(void* Obj)
{
	((FOctoHandStatus*)Obj)->bFinishAnimate = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_bFinishAnimate = { "bFinishAnimate", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FOctoHandStatus), &Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_bFinishAnimate_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bFinishAnimate_MetaData), NewProp_bFinishAnimate_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_animRandRate = { "animRandRate", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoHandStatus, animRandRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_animRandRate_MetaData), NewProp_animRandRate_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_animTime = { "animTime", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoHandStatus, animTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_animTime_MetaData), NewProp_animTime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_animIdleTime = { "animIdleTime", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoHandStatus, animIdleTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_animIdleTime_MetaData), NewProp_animIdleTime_MetaData) };
void Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_bCameraAnimation_SetBit(void* Obj)
{
	((FOctoHandStatus*)Obj)->bCameraAnimation = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_bCameraAnimation = { "bCameraAnimation", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FOctoHandStatus), &Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_bCameraAnimation_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bCameraAnimation_MetaData), NewProp_bCameraAnimation_MetaData) };
void Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_bLookInstance_SetBit(void* Obj)
{
	((FOctoHandStatus*)Obj)->bLookInstance = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_bLookInstance = { "bLookInstance", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FOctoHandStatus), &Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_bLookInstance_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bLookInstance_MetaData), NewProp_bLookInstance_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_grabbedObject = { "grabbedObject", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoHandStatus, grabbedObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_grabbedObject_MetaData), NewProp_grabbedObject_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FOctoHandStatus_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_hand_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_hand,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_handTransform,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_handBeforeMove,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_sizeHandNow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_targetPoint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_targetPointsArr_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_targetPointsArr,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_targetHitResult,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_checkPoint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_action_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_action,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_timeAttached,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_bBusyAlgo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_walkMoveHandTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_walkRotateHandTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_throwImpulse,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_bFinishAnimate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_animRandRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_animTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_animIdleTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_bCameraAnimation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_bLookInstance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewProp_grabbedObject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FOctoHandStatus_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FOctoHandStatus_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_OctopusBackpack,
	nullptr,
	&NewStructOps,
	"OctoHandStatus",
	Z_Construct_UScriptStruct_FOctoHandStatus_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FOctoHandStatus_Statics::PropPointers),
	sizeof(FOctoHandStatus),
	alignof(FOctoHandStatus),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000005),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FOctoHandStatus_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FOctoHandStatus_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FOctoHandStatus()
{
	if (!Z_Registration_Info_UScriptStruct_OctoHandStatus.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_OctoHandStatus.InnerSingleton, Z_Construct_UScriptStruct_FOctoHandStatus_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_OctoHandStatus.InnerSingleton;
}
// End ScriptStruct FOctoHandStatus

// Begin ScriptStruct FOctoTentaclesStruct
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_OctoTentaclesStruct;
class UScriptStruct* FOctoTentaclesStruct::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_OctoTentaclesStruct.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_OctoTentaclesStruct.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FOctoTentaclesStruct, (UObject*)Z_Construct_UPackage__Script_OctopusBackpack(), TEXT("OctoTentaclesStruct"));
	}
	return Z_Registration_Info_UScriptStruct_OctoTentaclesStruct.OuterSingleton;
}
template<> OCTOPUSBACKPACK_API UScriptStruct* StaticStruct<FOctoTentaclesStruct>()
{
	return FOctoTentaclesStruct::StaticStruct();
}
struct Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_hand_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_handSkeletalComponent_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_backpackComponent_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_handIndex_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_sphereCompsArr_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_splineMeshCompsArr_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_splineMeshBigCompsArr_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_constraintCompsArr_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_splineComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_newYawRotation_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_targetArrow_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_fallingArrow_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_grabArrow_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_originArrow_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_walkGrabArrow_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_walkArrow_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_junctionInstancedComp_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_startHandMesh_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_splineStartLength_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_splineCurrentLength_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_splineHideTime_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_splineStartPoint_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_effectActor_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusTypes.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_hand_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_hand;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_handSkeletalComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_backpackComponent;
	static const UECodeGen_Private::FIntPropertyParams NewProp_handIndex;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_sphereCompsArr_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_sphereCompsArr;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_splineMeshCompsArr_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_splineMeshCompsArr;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_splineMeshBigCompsArr_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_splineMeshBigCompsArr;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_constraintCompsArr_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_constraintCompsArr;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_splineComponent;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_newYawRotation;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_targetArrow;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_fallingArrow;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_grabArrow;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_originArrow;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_walkGrabArrow;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_walkArrow;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_junctionInstancedComp;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_startHandMesh;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_splineStartLength;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_splineCurrentLength;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_splineHideTime;
	static const UECodeGen_Private::FIntPropertyParams NewProp_splineStartPoint;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_effectActor;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FOctoTentaclesStruct>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_hand_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_hand = { "hand", nullptr, (EPropertyFlags)0x0010000000020815, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoTentaclesStruct, hand), Z_Construct_UEnum_OctopusBackpack_EOcto_Hand, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_hand_MetaData), NewProp_hand_MetaData) }; // 1375996686
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_handSkeletalComponent = { "handSkeletalComponent", nullptr, (EPropertyFlags)0x00100000000a081d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoTentaclesStruct, handSkeletalComponent), Z_Construct_UClass_USkeletalMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_handSkeletalComponent_MetaData), NewProp_handSkeletalComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_backpackComponent = { "backpackComponent", nullptr, (EPropertyFlags)0x00100000000a081d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoTentaclesStruct, backpackComponent), Z_Construct_UClass_UOctopusBackpackComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_backpackComponent_MetaData), NewProp_backpackComponent_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_handIndex = { "handIndex", nullptr, (EPropertyFlags)0x0010000000020815, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoTentaclesStruct, handIndex), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_handIndex_MetaData), NewProp_handIndex_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_sphereCompsArr_Inner = { "sphereCompsArr", nullptr, (EPropertyFlags)0x0000000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_USphereComponent_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_sphereCompsArr = { "sphereCompsArr", nullptr, (EPropertyFlags)0x0010008000000008, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoTentaclesStruct, sphereCompsArr), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_sphereCompsArr_MetaData), NewProp_sphereCompsArr_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_splineMeshCompsArr_Inner = { "splineMeshCompsArr", nullptr, (EPropertyFlags)0x0000000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_USplineMeshComponent_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_splineMeshCompsArr = { "splineMeshCompsArr", nullptr, (EPropertyFlags)0x0010008000000008, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoTentaclesStruct, splineMeshCompsArr), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_splineMeshCompsArr_MetaData), NewProp_splineMeshCompsArr_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_splineMeshBigCompsArr_Inner = { "splineMeshBigCompsArr", nullptr, (EPropertyFlags)0x0000000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_USplineMeshComponent_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_splineMeshBigCompsArr = { "splineMeshBigCompsArr", nullptr, (EPropertyFlags)0x0010008000000008, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoTentaclesStruct, splineMeshBigCompsArr), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_splineMeshBigCompsArr_MetaData), NewProp_splineMeshBigCompsArr_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_constraintCompsArr_Inner = { "constraintCompsArr", nullptr, (EPropertyFlags)0x0000000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UPhysicsConstraintComponent_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_constraintCompsArr = { "constraintCompsArr", nullptr, (EPropertyFlags)0x0010008000000008, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoTentaclesStruct, constraintCompsArr), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_constraintCompsArr_MetaData), NewProp_constraintCompsArr_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_splineComponent = { "splineComponent", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoTentaclesStruct, splineComponent), Z_Construct_UClass_USplineComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_splineComponent_MetaData), NewProp_splineComponent_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_newYawRotation = { "newYawRotation", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoTentaclesStruct, newYawRotation), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_newYawRotation_MetaData), NewProp_newYawRotation_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_targetArrow = { "targetArrow", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoTentaclesStruct, targetArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_targetArrow_MetaData), NewProp_targetArrow_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_fallingArrow = { "fallingArrow", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoTentaclesStruct, fallingArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_fallingArrow_MetaData), NewProp_fallingArrow_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_grabArrow = { "grabArrow", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoTentaclesStruct, grabArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_grabArrow_MetaData), NewProp_grabArrow_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_originArrow = { "originArrow", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoTentaclesStruct, originArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_originArrow_MetaData), NewProp_originArrow_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_walkGrabArrow = { "walkGrabArrow", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoTentaclesStruct, walkGrabArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_walkGrabArrow_MetaData), NewProp_walkGrabArrow_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_walkArrow = { "walkArrow", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoTentaclesStruct, walkArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_walkArrow_MetaData), NewProp_walkArrow_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_junctionInstancedComp = { "junctionInstancedComp", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoTentaclesStruct, junctionInstancedComp), Z_Construct_UClass_UInstancedStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_junctionInstancedComp_MetaData), NewProp_junctionInstancedComp_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_startHandMesh = { "startHandMesh", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoTentaclesStruct, startHandMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_startHandMesh_MetaData), NewProp_startHandMesh_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_splineStartLength = { "splineStartLength", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoTentaclesStruct, splineStartLength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_splineStartLength_MetaData), NewProp_splineStartLength_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_splineCurrentLength = { "splineCurrentLength", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoTentaclesStruct, splineCurrentLength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_splineCurrentLength_MetaData), NewProp_splineCurrentLength_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_splineHideTime = { "splineHideTime", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoTentaclesStruct, splineHideTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_splineHideTime_MetaData), NewProp_splineHideTime_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_splineStartPoint = { "splineStartPoint", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoTentaclesStruct, splineStartPoint), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_splineStartPoint_MetaData), NewProp_splineStartPoint_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_effectActor = { "effectActor", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOctoTentaclesStruct, effectActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_effectActor_MetaData), NewProp_effectActor_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_hand_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_hand,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_handSkeletalComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_backpackComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_handIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_sphereCompsArr_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_sphereCompsArr,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_splineMeshCompsArr_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_splineMeshCompsArr,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_splineMeshBigCompsArr_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_splineMeshBigCompsArr,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_constraintCompsArr_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_constraintCompsArr,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_splineComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_newYawRotation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_targetArrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_fallingArrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_grabArrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_originArrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_walkGrabArrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_walkArrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_junctionInstancedComp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_startHandMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_splineStartLength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_splineCurrentLength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_splineHideTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_splineStartPoint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewProp_effectActor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_OctopusBackpack,
	nullptr,
	&NewStructOps,
	"OctoTentaclesStruct",
	Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::PropPointers),
	sizeof(FOctoTentaclesStruct),
	alignof(FOctoTentaclesStruct),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000005),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FOctoTentaclesStruct()
{
	if (!Z_Registration_Info_UScriptStruct_OctoTentaclesStruct.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_OctoTentaclesStruct.InnerSingleton, Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_OctoTentaclesStruct.InnerSingleton;
}
// End ScriptStruct FOctoTentaclesStruct

// Begin Registration
struct Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusTypes_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EOcto_Move_StaticEnum, TEXT("EOcto_Move"), &Z_Registration_Info_UEnum_EOcto_Move, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3694688876U) },
		{ EOctoHandAction_StaticEnum, TEXT("EOctoHandAction"), &Z_Registration_Info_UEnum_EOctoHandAction, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2925050406U) },
		{ EOcto_Hand_StaticEnum, TEXT("EOcto_Hand"), &Z_Registration_Info_UEnum_EOcto_Hand, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1375996686U) },
		{ EOcto_HandPoint_StaticEnum, TEXT("EOcto_HandPoint"), &Z_Registration_Info_UEnum_EOcto_HandPoint, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2620307154U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FOctoHandStatus::StaticStruct, Z_Construct_UScriptStruct_FOctoHandStatus_Statics::NewStructOps, TEXT("OctoHandStatus"), &Z_Registration_Info_UScriptStruct_OctoHandStatus, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FOctoHandStatus), 3078096835U) },
		{ FOctoTentaclesStruct::StaticStruct, Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics::NewStructOps, TEXT("OctoTentaclesStruct"), &Z_Registration_Info_UScriptStruct_OctoTentaclesStruct, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FOctoTentaclesStruct), 4151897441U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusTypes_h_1778031369(TEXT("/Script/OctopusBackpack"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusTypes_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusTypes_h_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusTypes_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusTypes_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
