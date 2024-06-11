// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "OctopusBackpack/Public/OctopusBackpackComponent.h"
#include "OctopusBackpack/Public/OctopusTypes.h"
#include "Runtime/Engine/Classes/Engine/HitResult.h"
#include "Runtime/Engine/Classes/Engine/TimerHandle.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeOctopusBackpackComponent() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_ACharacter_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
ENGINE_API UClass* Z_Construct_UClass_UCurveFloat_NoRegister();
ENGINE_API UEnum* Z_Construct_UEnum_Engine_ECollisionChannel();
ENGINE_API UEnum* Z_Construct_UEnum_Engine_EObjectTypeQuery();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FHitResult();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FTimerHandle();
OCTOPUSBACKPACK_API UClass* Z_Construct_UClass_AOctopusBackpackActor_NoRegister();
OCTOPUSBACKPACK_API UClass* Z_Construct_UClass_UOctopusBackpackComponent();
OCTOPUSBACKPACK_API UClass* Z_Construct_UClass_UOctopusBackpackComponent_NoRegister();
OCTOPUSBACKPACK_API UFunction* Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusFlyingMode__DelegateSignature();
OCTOPUSBACKPACK_API UFunction* Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusReturnMovement__DelegateSignature();
OCTOPUSBACKPACK_API UScriptStruct* Z_Construct_UScriptStruct_FOctoHandStatus();
UPackage* Z_Construct_UPackage__Script_OctopusBackpack();
// End Cross Module References

// Begin Delegate FOctopusReturnMovement
struct Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusReturnMovement__DelegateSignature_Statics
{
	struct OctopusBackpackComponent_eventOctopusReturnMovement_Parms
	{
		FVector inScale;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_inScale;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusReturnMovement__DelegateSignature_Statics::NewProp_inScale = { "inScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OctopusBackpackComponent_eventOctopusReturnMovement_Parms, inScale), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusReturnMovement__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusReturnMovement__DelegateSignature_Statics::NewProp_inScale,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusReturnMovement__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusReturnMovement__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UOctopusBackpackComponent, nullptr, "OctopusReturnMovement__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusReturnMovement__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusReturnMovement__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusReturnMovement__DelegateSignature_Statics::OctopusBackpackComponent_eventOctopusReturnMovement_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00930000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusReturnMovement__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusReturnMovement__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusReturnMovement__DelegateSignature_Statics::OctopusBackpackComponent_eventOctopusReturnMovement_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusReturnMovement__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusReturnMovement__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void UOctopusBackpackComponent::FOctopusReturnMovement_DelegateWrapper(const FMulticastScriptDelegate& OctopusReturnMovement, FVector inScale)
{
	struct OctopusBackpackComponent_eventOctopusReturnMovement_Parms
	{
		FVector inScale;
	};
	OctopusBackpackComponent_eventOctopusReturnMovement_Parms Parms;
	Parms.inScale=inScale;
	OctopusReturnMovement.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FOctopusReturnMovement

// Begin Delegate FOctopusFlyingMode
struct Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusFlyingMode__DelegateSignature_Statics
{
	struct OctopusBackpackComponent_eventOctopusFlyingMode_Parms
	{
		bool bIsActivated;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
#endif // WITH_METADATA
	static void NewProp_bIsActivated_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsActivated;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusFlyingMode__DelegateSignature_Statics::NewProp_bIsActivated_SetBit(void* Obj)
{
	((OctopusBackpackComponent_eventOctopusFlyingMode_Parms*)Obj)->bIsActivated = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusFlyingMode__DelegateSignature_Statics::NewProp_bIsActivated = { "bIsActivated", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(OctopusBackpackComponent_eventOctopusFlyingMode_Parms), &Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusFlyingMode__DelegateSignature_Statics::NewProp_bIsActivated_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusFlyingMode__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusFlyingMode__DelegateSignature_Statics::NewProp_bIsActivated,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusFlyingMode__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusFlyingMode__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UOctopusBackpackComponent, nullptr, "OctopusFlyingMode__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusFlyingMode__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusFlyingMode__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusFlyingMode__DelegateSignature_Statics::OctopusBackpackComponent_eventOctopusFlyingMode_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusFlyingMode__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusFlyingMode__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusFlyingMode__DelegateSignature_Statics::OctopusBackpackComponent_eventOctopusFlyingMode_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusFlyingMode__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusFlyingMode__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void UOctopusBackpackComponent::FOctopusFlyingMode_DelegateWrapper(const FMulticastScriptDelegate& OctopusFlyingMode, bool bIsActivated)
{
	struct OctopusBackpackComponent_eventOctopusFlyingMode_Parms
	{
		bool bIsActivated;
	};
	OctopusBackpackComponent_eventOctopusFlyingMode_Parms Parms;
	Parms.bIsActivated=bIsActivated ? true : false;
	OctopusFlyingMode.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FOctopusFlyingMode

// Begin Class UOctopusBackpackComponent Function Attack
struct Z_Construct_UFunction_UOctopusBackpackComponent_Attack_Statics
{
	struct OctopusBackpackComponent_eventAttack_Parms
	{
		FHitResult targetHitResult;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_targetHitResult;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UOctopusBackpackComponent_Attack_Statics::NewProp_targetHitResult = { "targetHitResult", nullptr, (EPropertyFlags)0x0010008000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OctopusBackpackComponent_eventAttack_Parms, targetHitResult), Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(0, nullptr) }; // 4100991306
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UOctopusBackpackComponent_Attack_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOctopusBackpackComponent_Attack_Statics::NewProp_targetHitResult,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_Attack_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UOctopusBackpackComponent_Attack_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UOctopusBackpackComponent, nullptr, "Attack", nullptr, nullptr, Z_Construct_UFunction_UOctopusBackpackComponent_Attack_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_Attack_Statics::PropPointers), sizeof(Z_Construct_UFunction_UOctopusBackpackComponent_Attack_Statics::OctopusBackpackComponent_eventAttack_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_Attack_Statics::Function_MetaDataParams), Z_Construct_UFunction_UOctopusBackpackComponent_Attack_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UOctopusBackpackComponent_Attack_Statics::OctopusBackpackComponent_eventAttack_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UOctopusBackpackComponent_Attack()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UOctopusBackpackComponent_Attack_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UOctopusBackpackComponent::execAttack)
{
	P_GET_STRUCT(FHitResult,Z_Param_targetHitResult);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Attack(Z_Param_targetHitResult);
	P_NATIVE_END;
}
// End Class UOctopusBackpackComponent Function Attack

// Begin Class UOctopusBackpackComponent Function AttackHand
struct Z_Construct_UFunction_UOctopusBackpackComponent_AttackHand_Statics
{
	struct OctopusBackpackComponent_eventAttackHand_Parms
	{
		FHitResult targetHitResult;
		int32 handIndex;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_targetHitResult;
	static const UECodeGen_Private::FIntPropertyParams NewProp_handIndex;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UOctopusBackpackComponent_AttackHand_Statics::NewProp_targetHitResult = { "targetHitResult", nullptr, (EPropertyFlags)0x0010008000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OctopusBackpackComponent_eventAttackHand_Parms, targetHitResult), Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(0, nullptr) }; // 4100991306
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UOctopusBackpackComponent_AttackHand_Statics::NewProp_handIndex = { "handIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OctopusBackpackComponent_eventAttackHand_Parms, handIndex), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UOctopusBackpackComponent_AttackHand_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOctopusBackpackComponent_AttackHand_Statics::NewProp_targetHitResult,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOctopusBackpackComponent_AttackHand_Statics::NewProp_handIndex,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_AttackHand_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UOctopusBackpackComponent_AttackHand_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UOctopusBackpackComponent, nullptr, "AttackHand", nullptr, nullptr, Z_Construct_UFunction_UOctopusBackpackComponent_AttackHand_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_AttackHand_Statics::PropPointers), sizeof(Z_Construct_UFunction_UOctopusBackpackComponent_AttackHand_Statics::OctopusBackpackComponent_eventAttackHand_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_AttackHand_Statics::Function_MetaDataParams), Z_Construct_UFunction_UOctopusBackpackComponent_AttackHand_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UOctopusBackpackComponent_AttackHand_Statics::OctopusBackpackComponent_eventAttackHand_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UOctopusBackpackComponent_AttackHand()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UOctopusBackpackComponent_AttackHand_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UOctopusBackpackComponent::execAttackHand)
{
	P_GET_STRUCT(FHitResult,Z_Param_targetHitResult);
	P_GET_PROPERTY(FIntProperty,Z_Param_handIndex);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AttackHand(Z_Param_targetHitResult,Z_Param_handIndex);
	P_NATIVE_END;
}
// End Class UOctopusBackpackComponent Function AttackHand

// Begin Class UOctopusBackpackComponent Function Drop
struct Z_Construct_UFunction_UOctopusBackpackComponent_Drop_Statics
{
	struct OctopusBackpackComponent_eventDrop_Parms
	{
		int32 handIndex;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_handIndex;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UOctopusBackpackComponent_Drop_Statics::NewProp_handIndex = { "handIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OctopusBackpackComponent_eventDrop_Parms, handIndex), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UOctopusBackpackComponent_Drop_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOctopusBackpackComponent_Drop_Statics::NewProp_handIndex,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_Drop_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UOctopusBackpackComponent_Drop_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UOctopusBackpackComponent, nullptr, "Drop", nullptr, nullptr, Z_Construct_UFunction_UOctopusBackpackComponent_Drop_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_Drop_Statics::PropPointers), sizeof(Z_Construct_UFunction_UOctopusBackpackComponent_Drop_Statics::OctopusBackpackComponent_eventDrop_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_Drop_Statics::Function_MetaDataParams), Z_Construct_UFunction_UOctopusBackpackComponent_Drop_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UOctopusBackpackComponent_Drop_Statics::OctopusBackpackComponent_eventDrop_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UOctopusBackpackComponent_Drop()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UOctopusBackpackComponent_Drop_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UOctopusBackpackComponent::execDrop)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_handIndex);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Drop(Z_Param_handIndex);
	P_NATIVE_END;
}
// End Class UOctopusBackpackComponent Function Drop

// Begin Class UOctopusBackpackComponent Function DropAll
struct Z_Construct_UFunction_UOctopusBackpackComponent_DropAll_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UOctopusBackpackComponent_DropAll_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UOctopusBackpackComponent, nullptr, "DropAll", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_DropAll_Statics::Function_MetaDataParams), Z_Construct_UFunction_UOctopusBackpackComponent_DropAll_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UOctopusBackpackComponent_DropAll()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UOctopusBackpackComponent_DropAll_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UOctopusBackpackComponent::execDropAll)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DropAll();
	P_NATIVE_END;
}
// End Class UOctopusBackpackComponent Function DropAll

// Begin Class UOctopusBackpackComponent Function IsComponentGrabbed
struct Z_Construct_UFunction_UOctopusBackpackComponent_IsComponentGrabbed_Statics
{
	struct OctopusBackpackComponent_eventIsComponentGrabbed_Parms
	{
		UObject* checkObject;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_checkObject;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UOctopusBackpackComponent_IsComponentGrabbed_Statics::NewProp_checkObject = { "checkObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OctopusBackpackComponent_eventIsComponentGrabbed_Parms, checkObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UOctopusBackpackComponent_IsComponentGrabbed_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((OctopusBackpackComponent_eventIsComponentGrabbed_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UOctopusBackpackComponent_IsComponentGrabbed_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(OctopusBackpackComponent_eventIsComponentGrabbed_Parms), &Z_Construct_UFunction_UOctopusBackpackComponent_IsComponentGrabbed_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UOctopusBackpackComponent_IsComponentGrabbed_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOctopusBackpackComponent_IsComponentGrabbed_Statics::NewProp_checkObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOctopusBackpackComponent_IsComponentGrabbed_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_IsComponentGrabbed_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UOctopusBackpackComponent_IsComponentGrabbed_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UOctopusBackpackComponent, nullptr, "IsComponentGrabbed", nullptr, nullptr, Z_Construct_UFunction_UOctopusBackpackComponent_IsComponentGrabbed_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_IsComponentGrabbed_Statics::PropPointers), sizeof(Z_Construct_UFunction_UOctopusBackpackComponent_IsComponentGrabbed_Statics::OctopusBackpackComponent_eventIsComponentGrabbed_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_IsComponentGrabbed_Statics::Function_MetaDataParams), Z_Construct_UFunction_UOctopusBackpackComponent_IsComponentGrabbed_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UOctopusBackpackComponent_IsComponentGrabbed_Statics::OctopusBackpackComponent_eventIsComponentGrabbed_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UOctopusBackpackComponent_IsComponentGrabbed()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UOctopusBackpackComponent_IsComponentGrabbed_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UOctopusBackpackComponent::execIsComponentGrabbed)
{
	P_GET_OBJECT(UObject,Z_Param_checkObject);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsComponentGrabbed(Z_Param_checkObject);
	P_NATIVE_END;
}
// End Class UOctopusBackpackComponent Function IsComponentGrabbed

// Begin Class UOctopusBackpackComponent Function OctopusBackpackBattleMode
struct Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackBattleMode_Statics
{
	struct OctopusBackpackComponent_eventOctopusBackpackBattleMode_Parms
	{
		bool bActivate;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
#endif // WITH_METADATA
	static void NewProp_bActivate_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bActivate;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackBattleMode_Statics::NewProp_bActivate_SetBit(void* Obj)
{
	((OctopusBackpackComponent_eventOctopusBackpackBattleMode_Parms*)Obj)->bActivate = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackBattleMode_Statics::NewProp_bActivate = { "bActivate", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(OctopusBackpackComponent_eventOctopusBackpackBattleMode_Parms), &Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackBattleMode_Statics::NewProp_bActivate_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackBattleMode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackBattleMode_Statics::NewProp_bActivate,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackBattleMode_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackBattleMode_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UOctopusBackpackComponent, nullptr, "OctopusBackpackBattleMode", nullptr, nullptr, Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackBattleMode_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackBattleMode_Statics::PropPointers), sizeof(Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackBattleMode_Statics::OctopusBackpackComponent_eventOctopusBackpackBattleMode_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackBattleMode_Statics::Function_MetaDataParams), Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackBattleMode_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackBattleMode_Statics::OctopusBackpackComponent_eventOctopusBackpackBattleMode_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackBattleMode()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackBattleMode_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UOctopusBackpackComponent::execOctopusBackpackBattleMode)
{
	P_GET_UBOOL(Z_Param_bActivate);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OctopusBackpackBattleMode(Z_Param_bActivate);
	P_NATIVE_END;
}
// End Class UOctopusBackpackComponent Function OctopusBackpackBattleMode

// Begin Class UOctopusBackpackComponent Function OctopusBackpackFlyingMode
struct Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackFlyingMode_Statics
{
	struct OctopusBackpackComponent_eventOctopusBackpackFlyingMode_Parms
	{
		bool bActivate;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
#endif // WITH_METADATA
	static void NewProp_bActivate_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bActivate;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackFlyingMode_Statics::NewProp_bActivate_SetBit(void* Obj)
{
	((OctopusBackpackComponent_eventOctopusBackpackFlyingMode_Parms*)Obj)->bActivate = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackFlyingMode_Statics::NewProp_bActivate = { "bActivate", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(OctopusBackpackComponent_eventOctopusBackpackFlyingMode_Parms), &Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackFlyingMode_Statics::NewProp_bActivate_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackFlyingMode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackFlyingMode_Statics::NewProp_bActivate,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackFlyingMode_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackFlyingMode_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UOctopusBackpackComponent, nullptr, "OctopusBackpackFlyingMode", nullptr, nullptr, Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackFlyingMode_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackFlyingMode_Statics::PropPointers), sizeof(Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackFlyingMode_Statics::OctopusBackpackComponent_eventOctopusBackpackFlyingMode_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackFlyingMode_Statics::Function_MetaDataParams), Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackFlyingMode_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackFlyingMode_Statics::OctopusBackpackComponent_eventOctopusBackpackFlyingMode_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackFlyingMode()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackFlyingMode_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UOctopusBackpackComponent::execOctopusBackpackFlyingMode)
{
	P_GET_UBOOL(Z_Param_bActivate);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OctopusBackpackFlyingMode(Z_Param_bActivate);
	P_NATIVE_END;
}
// End Class UOctopusBackpackComponent Function OctopusBackpackFlyingMode

// Begin Class UOctopusBackpackComponent Function OctopusDamageActor
struct OctopusBackpackComponent_eventOctopusDamageActor_Parms
{
	AActor* actor;
};
static FName NAME_UOctopusBackpackComponent_OctopusDamageActor = FName(TEXT("OctopusDamageActor"));
void UOctopusBackpackComponent::OctopusDamageActor(AActor* actor)
{
	OctopusBackpackComponent_eventOctopusDamageActor_Parms Parms;
	Parms.actor=actor;
	ProcessEvent(FindFunctionChecked(NAME_UOctopusBackpackComponent_OctopusDamageActor),&Parms);
}
struct Z_Construct_UFunction_UOctopusBackpackComponent_OctopusDamageActor_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_actor;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UOctopusBackpackComponent_OctopusDamageActor_Statics::NewProp_actor = { "actor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OctopusBackpackComponent_eventOctopusDamageActor_Parms, actor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UOctopusBackpackComponent_OctopusDamageActor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOctopusBackpackComponent_OctopusDamageActor_Statics::NewProp_actor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_OctopusDamageActor_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UOctopusBackpackComponent_OctopusDamageActor_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UOctopusBackpackComponent, nullptr, "OctopusDamageActor", nullptr, nullptr, Z_Construct_UFunction_UOctopusBackpackComponent_OctopusDamageActor_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_OctopusDamageActor_Statics::PropPointers), sizeof(OctopusBackpackComponent_eventOctopusDamageActor_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_OctopusDamageActor_Statics::Function_MetaDataParams), Z_Construct_UFunction_UOctopusBackpackComponent_OctopusDamageActor_Statics::Function_MetaDataParams) };
static_assert(sizeof(OctopusBackpackComponent_eventOctopusDamageActor_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UOctopusBackpackComponent_OctopusDamageActor()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UOctopusBackpackComponent_OctopusDamageActor_Statics::FuncParams);
	}
	return ReturnFunction;
}
// End Class UOctopusBackpackComponent Function OctopusDamageActor

// Begin Class UOctopusBackpackComponent Function RegisterOctopusBackpack
struct Z_Construct_UFunction_UOctopusBackpackComponent_RegisterOctopusBackpack_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UOctopusBackpackComponent_RegisterOctopusBackpack_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UOctopusBackpackComponent, nullptr, "RegisterOctopusBackpack", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_RegisterOctopusBackpack_Statics::Function_MetaDataParams), Z_Construct_UFunction_UOctopusBackpackComponent_RegisterOctopusBackpack_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UOctopusBackpackComponent_RegisterOctopusBackpack()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UOctopusBackpackComponent_RegisterOctopusBackpack_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UOctopusBackpackComponent::execRegisterOctopusBackpack)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RegisterOctopusBackpack();
	P_NATIVE_END;
}
// End Class UOctopusBackpackComponent Function RegisterOctopusBackpack

// Begin Class UOctopusBackpackComponent Function SetMovementDirection
struct Z_Construct_UFunction_UOctopusBackpackComponent_SetMovementDirection_Statics
{
	struct OctopusBackpackComponent_eventSetMovementDirection_Parms
	{
		FVector setInputScale;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_setInputScale;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UOctopusBackpackComponent_SetMovementDirection_Statics::NewProp_setInputScale = { "setInputScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OctopusBackpackComponent_eventSetMovementDirection_Parms, setInputScale), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UOctopusBackpackComponent_SetMovementDirection_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOctopusBackpackComponent_SetMovementDirection_Statics::NewProp_setInputScale,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_SetMovementDirection_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UOctopusBackpackComponent_SetMovementDirection_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UOctopusBackpackComponent, nullptr, "SetMovementDirection", nullptr, nullptr, Z_Construct_UFunction_UOctopusBackpackComponent_SetMovementDirection_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_SetMovementDirection_Statics::PropPointers), sizeof(Z_Construct_UFunction_UOctopusBackpackComponent_SetMovementDirection_Statics::OctopusBackpackComponent_eventSetMovementDirection_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_SetMovementDirection_Statics::Function_MetaDataParams), Z_Construct_UFunction_UOctopusBackpackComponent_SetMovementDirection_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UOctopusBackpackComponent_SetMovementDirection_Statics::OctopusBackpackComponent_eventSetMovementDirection_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UOctopusBackpackComponent_SetMovementDirection()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UOctopusBackpackComponent_SetMovementDirection_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UOctopusBackpackComponent::execSetMovementDirection)
{
	P_GET_STRUCT(FVector,Z_Param_setInputScale);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetMovementDirection(Z_Param_setInputScale);
	P_NATIVE_END;
}
// End Class UOctopusBackpackComponent Function SetMovementDirection

// Begin Class UOctopusBackpackComponent Function Throw
struct Z_Construct_UFunction_UOctopusBackpackComponent_Throw_Statics
{
	struct OctopusBackpackComponent_eventThrow_Parms
	{
		int32 handIndex;
		FHitResult targetHitResult;
		float addThrowImpulse;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_handIndex;
	static const UECodeGen_Private::FStructPropertyParams NewProp_targetHitResult;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_addThrowImpulse;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UOctopusBackpackComponent_Throw_Statics::NewProp_handIndex = { "handIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OctopusBackpackComponent_eventThrow_Parms, handIndex), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UOctopusBackpackComponent_Throw_Statics::NewProp_targetHitResult = { "targetHitResult", nullptr, (EPropertyFlags)0x0010008000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OctopusBackpackComponent_eventThrow_Parms, targetHitResult), Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(0, nullptr) }; // 4100991306
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UOctopusBackpackComponent_Throw_Statics::NewProp_addThrowImpulse = { "addThrowImpulse", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OctopusBackpackComponent_eventThrow_Parms, addThrowImpulse), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UOctopusBackpackComponent_Throw_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOctopusBackpackComponent_Throw_Statics::NewProp_handIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOctopusBackpackComponent_Throw_Statics::NewProp_targetHitResult,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOctopusBackpackComponent_Throw_Statics::NewProp_addThrowImpulse,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_Throw_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UOctopusBackpackComponent_Throw_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UOctopusBackpackComponent, nullptr, "Throw", nullptr, nullptr, Z_Construct_UFunction_UOctopusBackpackComponent_Throw_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_Throw_Statics::PropPointers), sizeof(Z_Construct_UFunction_UOctopusBackpackComponent_Throw_Statics::OctopusBackpackComponent_eventThrow_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_Throw_Statics::Function_MetaDataParams), Z_Construct_UFunction_UOctopusBackpackComponent_Throw_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UOctopusBackpackComponent_Throw_Statics::OctopusBackpackComponent_eventThrow_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UOctopusBackpackComponent_Throw()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UOctopusBackpackComponent_Throw_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UOctopusBackpackComponent::execThrow)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_handIndex);
	P_GET_STRUCT(FHitResult,Z_Param_targetHitResult);
	P_GET_PROPERTY(FFloatProperty,Z_Param_addThrowImpulse);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Throw(Z_Param_handIndex,Z_Param_targetHitResult,Z_Param_addThrowImpulse);
	P_NATIVE_END;
}
// End Class UOctopusBackpackComponent Function Throw

// Begin Class UOctopusBackpackComponent Function ThrowAll
struct Z_Construct_UFunction_UOctopusBackpackComponent_ThrowAll_Statics
{
	struct OctopusBackpackComponent_eventThrowAll_Parms
	{
		FHitResult targetHitResult;
		float addThrowImpulse;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_targetHitResult;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_addThrowImpulse;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UOctopusBackpackComponent_ThrowAll_Statics::NewProp_targetHitResult = { "targetHitResult", nullptr, (EPropertyFlags)0x0010008000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OctopusBackpackComponent_eventThrowAll_Parms, targetHitResult), Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(0, nullptr) }; // 4100991306
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UOctopusBackpackComponent_ThrowAll_Statics::NewProp_addThrowImpulse = { "addThrowImpulse", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OctopusBackpackComponent_eventThrowAll_Parms, addThrowImpulse), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UOctopusBackpackComponent_ThrowAll_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOctopusBackpackComponent_ThrowAll_Statics::NewProp_targetHitResult,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOctopusBackpackComponent_ThrowAll_Statics::NewProp_addThrowImpulse,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_ThrowAll_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UOctopusBackpackComponent_ThrowAll_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UOctopusBackpackComponent, nullptr, "ThrowAll", nullptr, nullptr, Z_Construct_UFunction_UOctopusBackpackComponent_ThrowAll_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_ThrowAll_Statics::PropPointers), sizeof(Z_Construct_UFunction_UOctopusBackpackComponent_ThrowAll_Statics::OctopusBackpackComponent_eventThrowAll_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UOctopusBackpackComponent_ThrowAll_Statics::Function_MetaDataParams), Z_Construct_UFunction_UOctopusBackpackComponent_ThrowAll_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UOctopusBackpackComponent_ThrowAll_Statics::OctopusBackpackComponent_eventThrowAll_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UOctopusBackpackComponent_ThrowAll()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UOctopusBackpackComponent_ThrowAll_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UOctopusBackpackComponent::execThrowAll)
{
	P_GET_STRUCT(FHitResult,Z_Param_targetHitResult);
	P_GET_PROPERTY(FFloatProperty,Z_Param_addThrowImpulse);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ThrowAll(Z_Param_targetHitResult,Z_Param_addThrowImpulse);
	P_NATIVE_END;
}
// End Class UOctopusBackpackComponent Function ThrowAll

// Begin Class UOctopusBackpackComponent
void UOctopusBackpackComponent::StaticRegisterNativesUOctopusBackpackComponent()
{
	UClass* Class = UOctopusBackpackComponent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "Attack", &UOctopusBackpackComponent::execAttack },
		{ "AttackHand", &UOctopusBackpackComponent::execAttackHand },
		{ "Drop", &UOctopusBackpackComponent::execDrop },
		{ "DropAll", &UOctopusBackpackComponent::execDropAll },
		{ "IsComponentGrabbed", &UOctopusBackpackComponent::execIsComponentGrabbed },
		{ "OctopusBackpackBattleMode", &UOctopusBackpackComponent::execOctopusBackpackBattleMode },
		{ "OctopusBackpackFlyingMode", &UOctopusBackpackComponent::execOctopusBackpackFlyingMode },
		{ "RegisterOctopusBackpack", &UOctopusBackpackComponent::execRegisterOctopusBackpack },
		{ "SetMovementDirection", &UOctopusBackpackComponent::execSetMovementDirection },
		{ "Throw", &UOctopusBackpackComponent::execThrow },
		{ "ThrowAll", &UOctopusBackpackComponent::execThrowAll },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UOctopusBackpackComponent);
UClass* Z_Construct_UClass_UOctopusBackpackComponent_NoRegister()
{
	return UOctopusBackpackComponent::StaticClass();
}
struct Z_Construct_UClass_UOctopusBackpackComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "OctopusBackpackComponent.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnOctopusReturnMovement_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnOctopusFlyingMode_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_objectDynamicTypesArr_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "Comment", "// Check trace block by this\n" },
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
		{ "ToolTip", "Check trace block by this" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_walkMoveHandCurve_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_walkMoveReturnHandCurve_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_walkRotateHandCurve_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_attackMoveHandCurve_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_throwMoveHandCurve_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_fallingMoveHandCurve_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_movementDirection_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_inputScale_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_handsArr_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_grabbedActorsArr_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsFlyingModeActivate_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bHasAnchorPoint_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bBattleMode_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDevDebug_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_backPackOcto_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "Comment", "// UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = \"Octopus Backpack | Debug\")\n// bool bDebug = false;\n" },
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
		{ "ToolTip", "UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = \"Octopus Backpack | Debug\")\nbool bDebug = false;" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_animateHandle_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_animateRate_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_traceObjectTypesArr_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bFlyingDesiredState_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bRegisterFromPlayer_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_initializeHandle_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_initializeTime_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_myCharacter_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_searchDistance_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_actorsIgnoreArr_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bRegistred_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_boxRandAnim_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_randWalkBoxSize_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_throwDistanceHandMove_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_attackDistanceHandMove_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_moveDistance_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_checkBoxSize_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_maxHandDistance_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_maxHandDistanceSquared_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_breakDistance_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_breakDistanceSquared_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_nextPointDistance_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_nextPointDistanceSquared_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bFallingHands_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnOctopusReturnMovement;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnOctopusFlyingMode;
	static const UECodeGen_Private::FBytePropertyParams NewProp_objectDynamicTypesArr_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_objectDynamicTypesArr;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_walkMoveHandCurve;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_walkMoveReturnHandCurve;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_walkRotateHandCurve;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_attackMoveHandCurve;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_throwMoveHandCurve;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_fallingMoveHandCurve;
	static const UECodeGen_Private::FStructPropertyParams NewProp_movementDirection;
	static const UECodeGen_Private::FStructPropertyParams NewProp_inputScale;
	static const UECodeGen_Private::FStructPropertyParams NewProp_handsArr_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_handsArr;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_grabbedActorsArr_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_grabbedActorsArr;
	static void NewProp_bIsFlyingModeActivate_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsFlyingModeActivate;
	static void NewProp_bHasAnchorPoint_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bHasAnchorPoint;
	static void NewProp_bBattleMode_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bBattleMode;
	static void NewProp_bDevDebug_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDevDebug;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_backPackOcto;
	static const UECodeGen_Private::FStructPropertyParams NewProp_animateHandle;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_animateRate;
	static const UECodeGen_Private::FBytePropertyParams NewProp_traceObjectTypesArr_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_traceObjectTypesArr;
	static void NewProp_bFlyingDesiredState_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bFlyingDesiredState;
	static void NewProp_bRegisterFromPlayer_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bRegisterFromPlayer;
	static const UECodeGen_Private::FStructPropertyParams NewProp_initializeHandle;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_initializeTime;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_myCharacter;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_searchDistance;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_actorsIgnoreArr_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_actorsIgnoreArr;
	static void NewProp_bRegistred_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bRegistred;
	static const UECodeGen_Private::FStructPropertyParams NewProp_boxRandAnim;
	static const UECodeGen_Private::FStructPropertyParams NewProp_randWalkBoxSize;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_throwDistanceHandMove;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_attackDistanceHandMove;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_moveDistance;
	static const UECodeGen_Private::FStructPropertyParams NewProp_checkBoxSize;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_maxHandDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_maxHandDistanceSquared;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_breakDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_breakDistanceSquared;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_nextPointDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_nextPointDistanceSquared;
	static void NewProp_bFallingHands_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bFallingHands;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UOctopusBackpackComponent_Attack, "Attack" }, // 2341798578
		{ &Z_Construct_UFunction_UOctopusBackpackComponent_AttackHand, "AttackHand" }, // 2845096538
		{ &Z_Construct_UFunction_UOctopusBackpackComponent_Drop, "Drop" }, // 457368066
		{ &Z_Construct_UFunction_UOctopusBackpackComponent_DropAll, "DropAll" }, // 4185396248
		{ &Z_Construct_UFunction_UOctopusBackpackComponent_IsComponentGrabbed, "IsComponentGrabbed" }, // 381585208
		{ &Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackBattleMode, "OctopusBackpackBattleMode" }, // 3705907060
		{ &Z_Construct_UFunction_UOctopusBackpackComponent_OctopusBackpackFlyingMode, "OctopusBackpackFlyingMode" }, // 2556741829
		{ &Z_Construct_UFunction_UOctopusBackpackComponent_OctopusDamageActor, "OctopusDamageActor" }, // 2006078636
		{ &Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusFlyingMode__DelegateSignature, "OctopusFlyingMode__DelegateSignature" }, // 3406401794
		{ &Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusReturnMovement__DelegateSignature, "OctopusReturnMovement__DelegateSignature" }, // 33428079
		{ &Z_Construct_UFunction_UOctopusBackpackComponent_RegisterOctopusBackpack, "RegisterOctopusBackpack" }, // 4142846008
		{ &Z_Construct_UFunction_UOctopusBackpackComponent_SetMovementDirection, "SetMovementDirection" }, // 943718210
		{ &Z_Construct_UFunction_UOctopusBackpackComponent_Throw, "Throw" }, // 542161318
		{ &Z_Construct_UFunction_UOctopusBackpackComponent_ThrowAll, "ThrowAll" }, // 2535564766
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UOctopusBackpackComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_OnOctopusReturnMovement = { "OnOctopusReturnMovement", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, OnOctopusReturnMovement), Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusReturnMovement__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnOctopusReturnMovement_MetaData), NewProp_OnOctopusReturnMovement_MetaData) }; // 33428079
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_OnOctopusFlyingMode = { "OnOctopusFlyingMode", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, OnOctopusFlyingMode), Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusFlyingMode__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnOctopusFlyingMode_MetaData), NewProp_OnOctopusFlyingMode_MetaData) }; // 3406401794
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_objectDynamicTypesArr_Inner = { "objectDynamicTypesArr", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UEnum_Engine_ECollisionChannel, METADATA_PARAMS(0, nullptr) }; // 756624936
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_objectDynamicTypesArr = { "objectDynamicTypesArr", nullptr, (EPropertyFlags)0x0010000000010005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, objectDynamicTypesArr), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_objectDynamicTypesArr_MetaData), NewProp_objectDynamicTypesArr_MetaData) }; // 756624936
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_walkMoveHandCurve = { "walkMoveHandCurve", nullptr, (EPropertyFlags)0x0010000000010005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, walkMoveHandCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_walkMoveHandCurve_MetaData), NewProp_walkMoveHandCurve_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_walkMoveReturnHandCurve = { "walkMoveReturnHandCurve", nullptr, (EPropertyFlags)0x0010000000010005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, walkMoveReturnHandCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_walkMoveReturnHandCurve_MetaData), NewProp_walkMoveReturnHandCurve_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_walkRotateHandCurve = { "walkRotateHandCurve", nullptr, (EPropertyFlags)0x0010000000010005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, walkRotateHandCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_walkRotateHandCurve_MetaData), NewProp_walkRotateHandCurve_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_attackMoveHandCurve = { "attackMoveHandCurve", nullptr, (EPropertyFlags)0x0010000000010005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, attackMoveHandCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_attackMoveHandCurve_MetaData), NewProp_attackMoveHandCurve_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_throwMoveHandCurve = { "throwMoveHandCurve", nullptr, (EPropertyFlags)0x0010000000010005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, throwMoveHandCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_throwMoveHandCurve_MetaData), NewProp_throwMoveHandCurve_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_fallingMoveHandCurve = { "fallingMoveHandCurve", nullptr, (EPropertyFlags)0x0010000000010005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, fallingMoveHandCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_fallingMoveHandCurve_MetaData), NewProp_fallingMoveHandCurve_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_movementDirection = { "movementDirection", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, movementDirection), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_movementDirection_MetaData), NewProp_movementDirection_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_inputScale = { "inputScale", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, inputScale), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_inputScale_MetaData), NewProp_inputScale_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_handsArr_Inner = { "handsArr", nullptr, (EPropertyFlags)0x0000008000020000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FOctoHandStatus, METADATA_PARAMS(0, nullptr) }; // 3078096835
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_handsArr = { "handsArr", nullptr, (EPropertyFlags)0x0010008000020815, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, handsArr), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_handsArr_MetaData), NewProp_handsArr_MetaData) }; // 3078096835
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_grabbedActorsArr_Inner = { "grabbedActorsArr", nullptr, (EPropertyFlags)0x0000000000020000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_grabbedActorsArr = { "grabbedActorsArr", nullptr, (EPropertyFlags)0x0010000000020815, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, grabbedActorsArr), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_grabbedActorsArr_MetaData), NewProp_grabbedActorsArr_MetaData) };
void Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bIsFlyingModeActivate_SetBit(void* Obj)
{
	((UOctopusBackpackComponent*)Obj)->bIsFlyingModeActivate = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bIsFlyingModeActivate = { "bIsFlyingModeActivate", nullptr, (EPropertyFlags)0x0010000000020815, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UOctopusBackpackComponent), &Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bIsFlyingModeActivate_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsFlyingModeActivate_MetaData), NewProp_bIsFlyingModeActivate_MetaData) };
void Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bHasAnchorPoint_SetBit(void* Obj)
{
	((UOctopusBackpackComponent*)Obj)->bHasAnchorPoint = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bHasAnchorPoint = { "bHasAnchorPoint", nullptr, (EPropertyFlags)0x0010000000020815, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UOctopusBackpackComponent), &Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bHasAnchorPoint_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bHasAnchorPoint_MetaData), NewProp_bHasAnchorPoint_MetaData) };
void Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bBattleMode_SetBit(void* Obj)
{
	((UOctopusBackpackComponent*)Obj)->bBattleMode = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bBattleMode = { "bBattleMode", nullptr, (EPropertyFlags)0x0010000000020815, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UOctopusBackpackComponent), &Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bBattleMode_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bBattleMode_MetaData), NewProp_bBattleMode_MetaData) };
void Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bDevDebug_SetBit(void* Obj)
{
	((UOctopusBackpackComponent*)Obj)->bDevDebug = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bDevDebug = { "bDevDebug", nullptr, (EPropertyFlags)0x0010000000010015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UOctopusBackpackComponent), &Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bDevDebug_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDevDebug_MetaData), NewProp_bDevDebug_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_backPackOcto = { "backPackOcto", nullptr, (EPropertyFlags)0x0010000000020815, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, backPackOcto), Z_Construct_UClass_AOctopusBackpackActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_backPackOcto_MetaData), NewProp_backPackOcto_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_animateHandle = { "animateHandle", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, animateHandle), Z_Construct_UScriptStruct_FTimerHandle, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_animateHandle_MetaData), NewProp_animateHandle_MetaData) }; // 756291145
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_animateRate = { "animateRate", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, animateRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_animateRate_MetaData), NewProp_animateRate_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_traceObjectTypesArr_Inner = { "traceObjectTypesArr", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UEnum_Engine_EObjectTypeQuery, METADATA_PARAMS(0, nullptr) }; // 1798967895
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_traceObjectTypesArr = { "traceObjectTypesArr", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, traceObjectTypesArr), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_traceObjectTypesArr_MetaData), NewProp_traceObjectTypesArr_MetaData) }; // 1798967895
void Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bFlyingDesiredState_SetBit(void* Obj)
{
	((UOctopusBackpackComponent*)Obj)->bFlyingDesiredState = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bFlyingDesiredState = { "bFlyingDesiredState", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UOctopusBackpackComponent), &Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bFlyingDesiredState_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bFlyingDesiredState_MetaData), NewProp_bFlyingDesiredState_MetaData) };
void Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bRegisterFromPlayer_SetBit(void* Obj)
{
	((UOctopusBackpackComponent*)Obj)->bRegisterFromPlayer = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bRegisterFromPlayer = { "bRegisterFromPlayer", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UOctopusBackpackComponent), &Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bRegisterFromPlayer_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bRegisterFromPlayer_MetaData), NewProp_bRegisterFromPlayer_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_initializeHandle = { "initializeHandle", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, initializeHandle), Z_Construct_UScriptStruct_FTimerHandle, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_initializeHandle_MetaData), NewProp_initializeHandle_MetaData) }; // 756291145
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_initializeTime = { "initializeTime", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, initializeTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_initializeTime_MetaData), NewProp_initializeTime_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_myCharacter = { "myCharacter", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, myCharacter), Z_Construct_UClass_ACharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_myCharacter_MetaData), NewProp_myCharacter_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_searchDistance = { "searchDistance", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, searchDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_searchDistance_MetaData), NewProp_searchDistance_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_actorsIgnoreArr_Inner = { "actorsIgnoreArr", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_actorsIgnoreArr = { "actorsIgnoreArr", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, actorsIgnoreArr), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_actorsIgnoreArr_MetaData), NewProp_actorsIgnoreArr_MetaData) };
void Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bRegistred_SetBit(void* Obj)
{
	((UOctopusBackpackComponent*)Obj)->bRegistred = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bRegistred = { "bRegistred", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UOctopusBackpackComponent), &Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bRegistred_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bRegistred_MetaData), NewProp_bRegistred_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_boxRandAnim = { "boxRandAnim", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, boxRandAnim), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_boxRandAnim_MetaData), NewProp_boxRandAnim_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_randWalkBoxSize = { "randWalkBoxSize", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, randWalkBoxSize), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_randWalkBoxSize_MetaData), NewProp_randWalkBoxSize_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_throwDistanceHandMove = { "throwDistanceHandMove", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, throwDistanceHandMove), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_throwDistanceHandMove_MetaData), NewProp_throwDistanceHandMove_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_attackDistanceHandMove = { "attackDistanceHandMove", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, attackDistanceHandMove), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_attackDistanceHandMove_MetaData), NewProp_attackDistanceHandMove_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_moveDistance = { "moveDistance", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, moveDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_moveDistance_MetaData), NewProp_moveDistance_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_checkBoxSize = { "checkBoxSize", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, checkBoxSize), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_checkBoxSize_MetaData), NewProp_checkBoxSize_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_maxHandDistance = { "maxHandDistance", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, maxHandDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_maxHandDistance_MetaData), NewProp_maxHandDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_maxHandDistanceSquared = { "maxHandDistanceSquared", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, maxHandDistanceSquared), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_maxHandDistanceSquared_MetaData), NewProp_maxHandDistanceSquared_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_breakDistance = { "breakDistance", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, breakDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_breakDistance_MetaData), NewProp_breakDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_breakDistanceSquared = { "breakDistanceSquared", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, breakDistanceSquared), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_breakDistanceSquared_MetaData), NewProp_breakDistanceSquared_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_nextPointDistance = { "nextPointDistance", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, nextPointDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_nextPointDistance_MetaData), NewProp_nextPointDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_nextPointDistanceSquared = { "nextPointDistanceSquared", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOctopusBackpackComponent, nextPointDistanceSquared), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_nextPointDistanceSquared_MetaData), NewProp_nextPointDistanceSquared_MetaData) };
void Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bFallingHands_SetBit(void* Obj)
{
	((UOctopusBackpackComponent*)Obj)->bFallingHands = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bFallingHands = { "bFallingHands", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UOctopusBackpackComponent), &Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bFallingHands_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bFallingHands_MetaData), NewProp_bFallingHands_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UOctopusBackpackComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_OnOctopusReturnMovement,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_OnOctopusFlyingMode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_objectDynamicTypesArr_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_objectDynamicTypesArr,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_walkMoveHandCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_walkMoveReturnHandCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_walkRotateHandCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_attackMoveHandCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_throwMoveHandCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_fallingMoveHandCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_movementDirection,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_inputScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_handsArr_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_handsArr,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_grabbedActorsArr_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_grabbedActorsArr,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bIsFlyingModeActivate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bHasAnchorPoint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bBattleMode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bDevDebug,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_backPackOcto,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_animateHandle,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_animateRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_traceObjectTypesArr_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_traceObjectTypesArr,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bFlyingDesiredState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bRegisterFromPlayer,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_initializeHandle,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_initializeTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_myCharacter,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_searchDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_actorsIgnoreArr_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_actorsIgnoreArr,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bRegistred,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_boxRandAnim,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_randWalkBoxSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_throwDistanceHandMove,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_attackDistanceHandMove,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_moveDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_checkBoxSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_maxHandDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_maxHandDistanceSquared,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_breakDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_breakDistanceSquared,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_nextPointDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_nextPointDistanceSquared,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOctopusBackpackComponent_Statics::NewProp_bFallingHands,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UOctopusBackpackComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UOctopusBackpackComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_OctopusBackpack,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UOctopusBackpackComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UOctopusBackpackComponent_Statics::ClassParams = {
	&UOctopusBackpackComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UOctopusBackpackComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UOctopusBackpackComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UOctopusBackpackComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UOctopusBackpackComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UOctopusBackpackComponent()
{
	if (!Z_Registration_Info_UClass_UOctopusBackpackComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UOctopusBackpackComponent.OuterSingleton, Z_Construct_UClass_UOctopusBackpackComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UOctopusBackpackComponent.OuterSingleton;
}
template<> OCTOPUSBACKPACK_API UClass* StaticClass<UOctopusBackpackComponent>()
{
	return UOctopusBackpackComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UOctopusBackpackComponent);
UOctopusBackpackComponent::~UOctopusBackpackComponent() {}
// End Class UOctopusBackpackComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusBackpackComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UOctopusBackpackComponent, UOctopusBackpackComponent::StaticClass, TEXT("UOctopusBackpackComponent"), &Z_Registration_Info_UClass_UOctopusBackpackComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UOctopusBackpackComponent), 1442854574U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusBackpackComponent_h_267823612(TEXT("/Script/OctopusBackpack"),
	Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusBackpackComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusBackpackComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
