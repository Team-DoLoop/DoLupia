// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "OctopusBackpack/Public/OctopusBackpackActor.h"
#include "OctopusBackpack/Public/OctopusTypes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeOctopusBackpackActor() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UAnimBlueprint_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UArrowComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UCurveFloat_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USkeletalMesh_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMesh_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
OCTOPUSBACKPACK_API UClass* Z_Construct_UClass_AOctopusBackpackActor();
OCTOPUSBACKPACK_API UClass* Z_Construct_UClass_AOctopusBackpackActor_NoRegister();
OCTOPUSBACKPACK_API UClass* Z_Construct_UClass_UOctopusBackpackComponent_NoRegister();
OCTOPUSBACKPACK_API UScriptStruct* Z_Construct_UScriptStruct_FOctoTentaclesStruct();
UPackage* Z_Construct_UPackage__Script_OctopusBackpack();
// End Cross Module References

// Begin Class AOctopusBackpackActor Function ActivateBackpackEvent
struct OctopusBackpackActor_eventActivateBackpackEvent_Parms
{
	bool bActivate;
};
static FName NAME_AOctopusBackpackActor_ActivateBackpackEvent = FName(TEXT("ActivateBackpackEvent"));
void AOctopusBackpackActor::ActivateBackpackEvent(bool bActivate)
{
	OctopusBackpackActor_eventActivateBackpackEvent_Parms Parms;
	Parms.bActivate=bActivate ? true : false;
	ProcessEvent(FindFunctionChecked(NAME_AOctopusBackpackActor_ActivateBackpackEvent),&Parms);
}
struct Z_Construct_UFunction_AOctopusBackpackActor_ActivateBackpackEvent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
#endif // WITH_METADATA
	static void NewProp_bActivate_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bActivate;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_AOctopusBackpackActor_ActivateBackpackEvent_Statics::NewProp_bActivate_SetBit(void* Obj)
{
	((OctopusBackpackActor_eventActivateBackpackEvent_Parms*)Obj)->bActivate = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AOctopusBackpackActor_ActivateBackpackEvent_Statics::NewProp_bActivate = { "bActivate", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(OctopusBackpackActor_eventActivateBackpackEvent_Parms), &Z_Construct_UFunction_AOctopusBackpackActor_ActivateBackpackEvent_Statics::NewProp_bActivate_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AOctopusBackpackActor_ActivateBackpackEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AOctopusBackpackActor_ActivateBackpackEvent_Statics::NewProp_bActivate,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AOctopusBackpackActor_ActivateBackpackEvent_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AOctopusBackpackActor_ActivateBackpackEvent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AOctopusBackpackActor, nullptr, "ActivateBackpackEvent", nullptr, nullptr, Z_Construct_UFunction_AOctopusBackpackActor_ActivateBackpackEvent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AOctopusBackpackActor_ActivateBackpackEvent_Statics::PropPointers), sizeof(OctopusBackpackActor_eventActivateBackpackEvent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AOctopusBackpackActor_ActivateBackpackEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_AOctopusBackpackActor_ActivateBackpackEvent_Statics::Function_MetaDataParams) };
static_assert(sizeof(OctopusBackpackActor_eventActivateBackpackEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AOctopusBackpackActor_ActivateBackpackEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AOctopusBackpackActor_ActivateBackpackEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
// End Class AOctopusBackpackActor Function ActivateBackpackEvent

// Begin Class AOctopusBackpackActor Function AttachedEvent
struct OctopusBackpackActor_eventAttachedEvent_Parms
{
	FOctoTentaclesStruct tentacle;
};
static FName NAME_AOctopusBackpackActor_AttachedEvent = FName(TEXT("AttachedEvent"));
void AOctopusBackpackActor::AttachedEvent(FOctoTentaclesStruct tentacle)
{
	OctopusBackpackActor_eventAttachedEvent_Parms Parms;
	Parms.tentacle=tentacle;
	ProcessEvent(FindFunctionChecked(NAME_AOctopusBackpackActor_AttachedEvent),&Parms);
}
struct Z_Construct_UFunction_AOctopusBackpackActor_AttachedEvent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_tentacle;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AOctopusBackpackActor_AttachedEvent_Statics::NewProp_tentacle = { "tentacle", nullptr, (EPropertyFlags)0x0010008000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OctopusBackpackActor_eventAttachedEvent_Parms, tentacle), Z_Construct_UScriptStruct_FOctoTentaclesStruct, METADATA_PARAMS(0, nullptr) }; // 4151897441
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AOctopusBackpackActor_AttachedEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AOctopusBackpackActor_AttachedEvent_Statics::NewProp_tentacle,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AOctopusBackpackActor_AttachedEvent_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AOctopusBackpackActor_AttachedEvent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AOctopusBackpackActor, nullptr, "AttachedEvent", nullptr, nullptr, Z_Construct_UFunction_AOctopusBackpackActor_AttachedEvent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AOctopusBackpackActor_AttachedEvent_Statics::PropPointers), sizeof(OctopusBackpackActor_eventAttachedEvent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AOctopusBackpackActor_AttachedEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_AOctopusBackpackActor_AttachedEvent_Statics::Function_MetaDataParams) };
static_assert(sizeof(OctopusBackpackActor_eventAttachedEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AOctopusBackpackActor_AttachedEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AOctopusBackpackActor_AttachedEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
// End Class AOctopusBackpackActor Function AttachedEvent

// Begin Class AOctopusBackpackActor Function AttackMoveEvent
struct OctopusBackpackActor_eventAttackMoveEvent_Parms
{
	FOctoTentaclesStruct tentacle;
};
static FName NAME_AOctopusBackpackActor_AttackMoveEvent = FName(TEXT("AttackMoveEvent"));
void AOctopusBackpackActor::AttackMoveEvent(FOctoTentaclesStruct tentacle)
{
	OctopusBackpackActor_eventAttackMoveEvent_Parms Parms;
	Parms.tentacle=tentacle;
	ProcessEvent(FindFunctionChecked(NAME_AOctopusBackpackActor_AttackMoveEvent),&Parms);
}
struct Z_Construct_UFunction_AOctopusBackpackActor_AttackMoveEvent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_tentacle;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AOctopusBackpackActor_AttackMoveEvent_Statics::NewProp_tentacle = { "tentacle", nullptr, (EPropertyFlags)0x0010008000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OctopusBackpackActor_eventAttackMoveEvent_Parms, tentacle), Z_Construct_UScriptStruct_FOctoTentaclesStruct, METADATA_PARAMS(0, nullptr) }; // 4151897441
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AOctopusBackpackActor_AttackMoveEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AOctopusBackpackActor_AttackMoveEvent_Statics::NewProp_tentacle,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AOctopusBackpackActor_AttackMoveEvent_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AOctopusBackpackActor_AttackMoveEvent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AOctopusBackpackActor, nullptr, "AttackMoveEvent", nullptr, nullptr, Z_Construct_UFunction_AOctopusBackpackActor_AttackMoveEvent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AOctopusBackpackActor_AttackMoveEvent_Statics::PropPointers), sizeof(OctopusBackpackActor_eventAttackMoveEvent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AOctopusBackpackActor_AttackMoveEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_AOctopusBackpackActor_AttackMoveEvent_Statics::Function_MetaDataParams) };
static_assert(sizeof(OctopusBackpackActor_eventAttackMoveEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AOctopusBackpackActor_AttackMoveEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AOctopusBackpackActor_AttackMoveEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
// End Class AOctopusBackpackActor Function AttackMoveEvent

// Begin Class AOctopusBackpackActor Function GrabbedEvent
struct OctopusBackpackActor_eventGrabbedEvent_Parms
{
	FOctoTentaclesStruct tentacle;
};
static FName NAME_AOctopusBackpackActor_GrabbedEvent = FName(TEXT("GrabbedEvent"));
void AOctopusBackpackActor::GrabbedEvent(FOctoTentaclesStruct tentacle)
{
	OctopusBackpackActor_eventGrabbedEvent_Parms Parms;
	Parms.tentacle=tentacle;
	ProcessEvent(FindFunctionChecked(NAME_AOctopusBackpackActor_GrabbedEvent),&Parms);
}
struct Z_Construct_UFunction_AOctopusBackpackActor_GrabbedEvent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_tentacle;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AOctopusBackpackActor_GrabbedEvent_Statics::NewProp_tentacle = { "tentacle", nullptr, (EPropertyFlags)0x0010008000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OctopusBackpackActor_eventGrabbedEvent_Parms, tentacle), Z_Construct_UScriptStruct_FOctoTentaclesStruct, METADATA_PARAMS(0, nullptr) }; // 4151897441
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AOctopusBackpackActor_GrabbedEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AOctopusBackpackActor_GrabbedEvent_Statics::NewProp_tentacle,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AOctopusBackpackActor_GrabbedEvent_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AOctopusBackpackActor_GrabbedEvent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AOctopusBackpackActor, nullptr, "GrabbedEvent", nullptr, nullptr, Z_Construct_UFunction_AOctopusBackpackActor_GrabbedEvent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AOctopusBackpackActor_GrabbedEvent_Statics::PropPointers), sizeof(OctopusBackpackActor_eventGrabbedEvent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AOctopusBackpackActor_GrabbedEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_AOctopusBackpackActor_GrabbedEvent_Statics::Function_MetaDataParams) };
static_assert(sizeof(OctopusBackpackActor_eventGrabbedEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AOctopusBackpackActor_GrabbedEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AOctopusBackpackActor_GrabbedEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
// End Class AOctopusBackpackActor Function GrabbedEvent

// Begin Class AOctopusBackpackActor Function MoveToAttachPointEvent
struct OctopusBackpackActor_eventMoveToAttachPointEvent_Parms
{
	FOctoTentaclesStruct tentacle;
};
static FName NAME_AOctopusBackpackActor_MoveToAttachPointEvent = FName(TEXT("MoveToAttachPointEvent"));
void AOctopusBackpackActor::MoveToAttachPointEvent(FOctoTentaclesStruct tentacle)
{
	OctopusBackpackActor_eventMoveToAttachPointEvent_Parms Parms;
	Parms.tentacle=tentacle;
	ProcessEvent(FindFunctionChecked(NAME_AOctopusBackpackActor_MoveToAttachPointEvent),&Parms);
}
struct Z_Construct_UFunction_AOctopusBackpackActor_MoveToAttachPointEvent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_tentacle;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AOctopusBackpackActor_MoveToAttachPointEvent_Statics::NewProp_tentacle = { "tentacle", nullptr, (EPropertyFlags)0x0010008000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OctopusBackpackActor_eventMoveToAttachPointEvent_Parms, tentacle), Z_Construct_UScriptStruct_FOctoTentaclesStruct, METADATA_PARAMS(0, nullptr) }; // 4151897441
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AOctopusBackpackActor_MoveToAttachPointEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AOctopusBackpackActor_MoveToAttachPointEvent_Statics::NewProp_tentacle,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AOctopusBackpackActor_MoveToAttachPointEvent_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AOctopusBackpackActor_MoveToAttachPointEvent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AOctopusBackpackActor, nullptr, "MoveToAttachPointEvent", nullptr, nullptr, Z_Construct_UFunction_AOctopusBackpackActor_MoveToAttachPointEvent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AOctopusBackpackActor_MoveToAttachPointEvent_Statics::PropPointers), sizeof(OctopusBackpackActor_eventMoveToAttachPointEvent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AOctopusBackpackActor_MoveToAttachPointEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_AOctopusBackpackActor_MoveToAttachPointEvent_Statics::Function_MetaDataParams) };
static_assert(sizeof(OctopusBackpackActor_eventMoveToAttachPointEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AOctopusBackpackActor_MoveToAttachPointEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AOctopusBackpackActor_MoveToAttachPointEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
// End Class AOctopusBackpackActor Function MoveToAttachPointEvent

// Begin Class AOctopusBackpackActor Function ReturnEvent
struct OctopusBackpackActor_eventReturnEvent_Parms
{
	FOctoTentaclesStruct tentacle;
};
static FName NAME_AOctopusBackpackActor_ReturnEvent = FName(TEXT("ReturnEvent"));
void AOctopusBackpackActor::ReturnEvent(FOctoTentaclesStruct tentacle)
{
	OctopusBackpackActor_eventReturnEvent_Parms Parms;
	Parms.tentacle=tentacle;
	ProcessEvent(FindFunctionChecked(NAME_AOctopusBackpackActor_ReturnEvent),&Parms);
}
struct Z_Construct_UFunction_AOctopusBackpackActor_ReturnEvent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_tentacle;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AOctopusBackpackActor_ReturnEvent_Statics::NewProp_tentacle = { "tentacle", nullptr, (EPropertyFlags)0x0010008000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OctopusBackpackActor_eventReturnEvent_Parms, tentacle), Z_Construct_UScriptStruct_FOctoTentaclesStruct, METADATA_PARAMS(0, nullptr) }; // 4151897441
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AOctopusBackpackActor_ReturnEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AOctopusBackpackActor_ReturnEvent_Statics::NewProp_tentacle,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AOctopusBackpackActor_ReturnEvent_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AOctopusBackpackActor_ReturnEvent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AOctopusBackpackActor, nullptr, "ReturnEvent", nullptr, nullptr, Z_Construct_UFunction_AOctopusBackpackActor_ReturnEvent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AOctopusBackpackActor_ReturnEvent_Statics::PropPointers), sizeof(OctopusBackpackActor_eventReturnEvent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AOctopusBackpackActor_ReturnEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_AOctopusBackpackActor_ReturnEvent_Statics::Function_MetaDataParams) };
static_assert(sizeof(OctopusBackpackActor_eventReturnEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AOctopusBackpackActor_ReturnEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AOctopusBackpackActor_ReturnEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
// End Class AOctopusBackpackActor Function ReturnEvent

// Begin Class AOctopusBackpackActor
void AOctopusBackpackActor::StaticRegisterNativesAOctopusBackpackActor()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AOctopusBackpackActor);
UClass* Z_Construct_UClass_AOctopusBackpackActor_NoRegister()
{
	return AOctopusBackpackActor::StaticClass();
}
struct Z_Construct_UClass_AOctopusBackpackActor_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "OctopusBackpackActor.h" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_sceneComponent_MetaData[] = {
		{ "Category", "Component" },
		{ "Comment", "//************************************************************************\n// Component                                                                  \n//************************************************************************\n" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
		{ "ToolTip", "Component" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LeftBottomHandStartMesh_MetaData[] = {
		{ "Category", "Component" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RightBottomHandStartMesh_MetaData[] = {
		{ "Category", "Component" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LeftTopHandStartMesh_MetaData[] = {
		{ "Category", "Component" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RightTopHandStartMesh_MetaData[] = {
		{ "Category", "Component" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LeftBottomHandFallingArrow_MetaData[] = {
		{ "Category", "Component" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RightBottomHandFallingArrow_MetaData[] = {
		{ "Category", "Component" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LeftTopHandFallingArrow_MetaData[] = {
		{ "Category", "Component" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RightTopHandFallingArrow_MetaData[] = {
		{ "Category", "Component" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LeftBottomHandStartArrow_MetaData[] = {
		{ "Category", "Component" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RightBottomHandStartArrow_MetaData[] = {
		{ "Category", "Component" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LeftTopHandStartArrow_MetaData[] = {
		{ "Category", "Component" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RightTopHandStartArrow_MetaData[] = {
		{ "Category", "Component" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LeftBottomHandGrabArrow_MetaData[] = {
		{ "Category", "Component" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RightBottomHandGrabArrow_MetaData[] = {
		{ "Category", "Component" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LeftTopHandGrabArrow_MetaData[] = {
		{ "Category", "Component" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RightTopHandGrabArrow_MetaData[] = {
		{ "Category", "Component" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LeftBottomHandWalkArrow_MetaData[] = {
		{ "Category", "Component" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RightBottomHandWalkArrow_MetaData[] = {
		{ "Category", "Component" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LeftTopHandWalkArrow_MetaData[] = {
		{ "Category", "Component" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RightTopHandWalkArrow_MetaData[] = {
		{ "Category", "Component" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LeftBottomHandWalkGrabArrow_MetaData[] = {
		{ "Category", "Component" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RightBottomHandWalkGrabArrow_MetaData[] = {
		{ "Category", "Component" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LeftTopHandWalkGrabArrow_MetaData[] = {
		{ "Category", "Component" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RightTopHandWalkGrabArrow_MetaData[] = {
		{ "Category", "Component" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tentaclesArr_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tentaclesStaticMesh_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tentaclesBigStaticMesh_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_handSkeletalMesh_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_junctionStaticMesh_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_leftBottomHandAnimationClass_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_rightBottomHandAnimationClass_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_leftTopHandAnimationClass_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_rightTopHandAnimationClass_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_walkHandStretchCurve_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_attackHandStretchCurve_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_handAngularLimitCurve_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_effectActorsArr_MetaData[] = {
		{ "Category", "Octopus Backpack | Parameters" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsHandsShowed_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_sectionCount_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_sphereRadius_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_sphereSpacer_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_sphereMass_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_junctionCount_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_junctionEndSpace_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_maxBrokenHandDistance_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_maxBrokenHandDistanceSquared_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_physDamping__MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsActivateBackpack_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_sphereDistanceLoc_MetaData[] = {
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_backpackComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/OctopusBackpackActor.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_sceneComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LeftBottomHandStartMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RightBottomHandStartMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LeftTopHandStartMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RightTopHandStartMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LeftBottomHandFallingArrow;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RightBottomHandFallingArrow;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LeftTopHandFallingArrow;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RightTopHandFallingArrow;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LeftBottomHandStartArrow;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RightBottomHandStartArrow;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LeftTopHandStartArrow;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RightTopHandStartArrow;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LeftBottomHandGrabArrow;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RightBottomHandGrabArrow;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LeftTopHandGrabArrow;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RightTopHandGrabArrow;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LeftBottomHandWalkArrow;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RightBottomHandWalkArrow;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LeftTopHandWalkArrow;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RightTopHandWalkArrow;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LeftBottomHandWalkGrabArrow;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RightBottomHandWalkGrabArrow;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LeftTopHandWalkGrabArrow;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RightTopHandWalkGrabArrow;
	static const UECodeGen_Private::FStructPropertyParams NewProp_tentaclesArr_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_tentaclesArr;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_tentaclesStaticMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_tentaclesBigStaticMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_handSkeletalMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_junctionStaticMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_leftBottomHandAnimationClass;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_rightBottomHandAnimationClass;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_leftTopHandAnimationClass;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_rightTopHandAnimationClass;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_walkHandStretchCurve;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_attackHandStretchCurve;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_handAngularLimitCurve;
	static const UECodeGen_Private::FClassPropertyParams NewProp_effectActorsArr_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_effectActorsArr;
	static void NewProp_bIsHandsShowed_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsHandsShowed;
	static const UECodeGen_Private::FIntPropertyParams NewProp_sectionCount;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_sphereRadius;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_sphereSpacer;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_sphereMass;
	static const UECodeGen_Private::FIntPropertyParams NewProp_junctionCount;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_junctionEndSpace;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_maxBrokenHandDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_maxBrokenHandDistanceSquared;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_physDamping_;
	static void NewProp_bIsActivateBackpack_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsActivateBackpack;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_sphereDistanceLoc;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_backpackComponent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AOctopusBackpackActor_ActivateBackpackEvent, "ActivateBackpackEvent" }, // 4132594575
		{ &Z_Construct_UFunction_AOctopusBackpackActor_AttachedEvent, "AttachedEvent" }, // 726120977
		{ &Z_Construct_UFunction_AOctopusBackpackActor_AttackMoveEvent, "AttackMoveEvent" }, // 929146177
		{ &Z_Construct_UFunction_AOctopusBackpackActor_GrabbedEvent, "GrabbedEvent" }, // 1023032055
		{ &Z_Construct_UFunction_AOctopusBackpackActor_MoveToAttachPointEvent, "MoveToAttachPointEvent" }, // 2993750838
		{ &Z_Construct_UFunction_AOctopusBackpackActor_ReturnEvent, "ReturnEvent" }, // 1633132070
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AOctopusBackpackActor>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_sceneComponent = { "sceneComponent", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, sceneComponent), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_sceneComponent_MetaData), NewProp_sceneComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_LeftBottomHandStartMesh = { "LeftBottomHandStartMesh", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, LeftBottomHandStartMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LeftBottomHandStartMesh_MetaData), NewProp_LeftBottomHandStartMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_RightBottomHandStartMesh = { "RightBottomHandStartMesh", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, RightBottomHandStartMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RightBottomHandStartMesh_MetaData), NewProp_RightBottomHandStartMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_LeftTopHandStartMesh = { "LeftTopHandStartMesh", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, LeftTopHandStartMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LeftTopHandStartMesh_MetaData), NewProp_LeftTopHandStartMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_RightTopHandStartMesh = { "RightTopHandStartMesh", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, RightTopHandStartMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RightTopHandStartMesh_MetaData), NewProp_RightTopHandStartMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_LeftBottomHandFallingArrow = { "LeftBottomHandFallingArrow", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, LeftBottomHandFallingArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LeftBottomHandFallingArrow_MetaData), NewProp_LeftBottomHandFallingArrow_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_RightBottomHandFallingArrow = { "RightBottomHandFallingArrow", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, RightBottomHandFallingArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RightBottomHandFallingArrow_MetaData), NewProp_RightBottomHandFallingArrow_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_LeftTopHandFallingArrow = { "LeftTopHandFallingArrow", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, LeftTopHandFallingArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LeftTopHandFallingArrow_MetaData), NewProp_LeftTopHandFallingArrow_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_RightTopHandFallingArrow = { "RightTopHandFallingArrow", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, RightTopHandFallingArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RightTopHandFallingArrow_MetaData), NewProp_RightTopHandFallingArrow_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_LeftBottomHandStartArrow = { "LeftBottomHandStartArrow", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, LeftBottomHandStartArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LeftBottomHandStartArrow_MetaData), NewProp_LeftBottomHandStartArrow_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_RightBottomHandStartArrow = { "RightBottomHandStartArrow", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, RightBottomHandStartArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RightBottomHandStartArrow_MetaData), NewProp_RightBottomHandStartArrow_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_LeftTopHandStartArrow = { "LeftTopHandStartArrow", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, LeftTopHandStartArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LeftTopHandStartArrow_MetaData), NewProp_LeftTopHandStartArrow_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_RightTopHandStartArrow = { "RightTopHandStartArrow", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, RightTopHandStartArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RightTopHandStartArrow_MetaData), NewProp_RightTopHandStartArrow_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_LeftBottomHandGrabArrow = { "LeftBottomHandGrabArrow", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, LeftBottomHandGrabArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LeftBottomHandGrabArrow_MetaData), NewProp_LeftBottomHandGrabArrow_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_RightBottomHandGrabArrow = { "RightBottomHandGrabArrow", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, RightBottomHandGrabArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RightBottomHandGrabArrow_MetaData), NewProp_RightBottomHandGrabArrow_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_LeftTopHandGrabArrow = { "LeftTopHandGrabArrow", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, LeftTopHandGrabArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LeftTopHandGrabArrow_MetaData), NewProp_LeftTopHandGrabArrow_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_RightTopHandGrabArrow = { "RightTopHandGrabArrow", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, RightTopHandGrabArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RightTopHandGrabArrow_MetaData), NewProp_RightTopHandGrabArrow_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_LeftBottomHandWalkArrow = { "LeftBottomHandWalkArrow", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, LeftBottomHandWalkArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LeftBottomHandWalkArrow_MetaData), NewProp_LeftBottomHandWalkArrow_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_RightBottomHandWalkArrow = { "RightBottomHandWalkArrow", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, RightBottomHandWalkArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RightBottomHandWalkArrow_MetaData), NewProp_RightBottomHandWalkArrow_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_LeftTopHandWalkArrow = { "LeftTopHandWalkArrow", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, LeftTopHandWalkArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LeftTopHandWalkArrow_MetaData), NewProp_LeftTopHandWalkArrow_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_RightTopHandWalkArrow = { "RightTopHandWalkArrow", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, RightTopHandWalkArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RightTopHandWalkArrow_MetaData), NewProp_RightTopHandWalkArrow_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_LeftBottomHandWalkGrabArrow = { "LeftBottomHandWalkGrabArrow", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, LeftBottomHandWalkGrabArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LeftBottomHandWalkGrabArrow_MetaData), NewProp_LeftBottomHandWalkGrabArrow_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_RightBottomHandWalkGrabArrow = { "RightBottomHandWalkGrabArrow", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, RightBottomHandWalkGrabArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RightBottomHandWalkGrabArrow_MetaData), NewProp_RightBottomHandWalkGrabArrow_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_LeftTopHandWalkGrabArrow = { "LeftTopHandWalkGrabArrow", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, LeftTopHandWalkGrabArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LeftTopHandWalkGrabArrow_MetaData), NewProp_LeftTopHandWalkGrabArrow_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_RightTopHandWalkGrabArrow = { "RightTopHandWalkGrabArrow", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, RightTopHandWalkGrabArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RightTopHandWalkGrabArrow_MetaData), NewProp_RightTopHandWalkGrabArrow_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_tentaclesArr_Inner = { "tentaclesArr", nullptr, (EPropertyFlags)0x0000008000020000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FOctoTentaclesStruct, METADATA_PARAMS(0, nullptr) }; // 4151897441
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_tentaclesArr = { "tentaclesArr", nullptr, (EPropertyFlags)0x0010008000020815, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, tentaclesArr), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tentaclesArr_MetaData), NewProp_tentaclesArr_MetaData) }; // 4151897441
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_tentaclesStaticMesh = { "tentaclesStaticMesh", nullptr, (EPropertyFlags)0x0010000000010005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, tentaclesStaticMesh), Z_Construct_UClass_UStaticMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tentaclesStaticMesh_MetaData), NewProp_tentaclesStaticMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_tentaclesBigStaticMesh = { "tentaclesBigStaticMesh", nullptr, (EPropertyFlags)0x0010000000010005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, tentaclesBigStaticMesh), Z_Construct_UClass_UStaticMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tentaclesBigStaticMesh_MetaData), NewProp_tentaclesBigStaticMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_handSkeletalMesh = { "handSkeletalMesh", nullptr, (EPropertyFlags)0x0010000000010005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, handSkeletalMesh), Z_Construct_UClass_USkeletalMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_handSkeletalMesh_MetaData), NewProp_handSkeletalMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_junctionStaticMesh = { "junctionStaticMesh", nullptr, (EPropertyFlags)0x0010000000010005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, junctionStaticMesh), Z_Construct_UClass_UStaticMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_junctionStaticMesh_MetaData), NewProp_junctionStaticMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_leftBottomHandAnimationClass = { "leftBottomHandAnimationClass", nullptr, (EPropertyFlags)0x0010000000010005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, leftBottomHandAnimationClass), Z_Construct_UClass_UAnimBlueprint_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_leftBottomHandAnimationClass_MetaData), NewProp_leftBottomHandAnimationClass_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_rightBottomHandAnimationClass = { "rightBottomHandAnimationClass", nullptr, (EPropertyFlags)0x0010000000010005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, rightBottomHandAnimationClass), Z_Construct_UClass_UAnimBlueprint_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_rightBottomHandAnimationClass_MetaData), NewProp_rightBottomHandAnimationClass_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_leftTopHandAnimationClass = { "leftTopHandAnimationClass", nullptr, (EPropertyFlags)0x0010000000010005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, leftTopHandAnimationClass), Z_Construct_UClass_UAnimBlueprint_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_leftTopHandAnimationClass_MetaData), NewProp_leftTopHandAnimationClass_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_rightTopHandAnimationClass = { "rightTopHandAnimationClass", nullptr, (EPropertyFlags)0x0010000000010005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, rightTopHandAnimationClass), Z_Construct_UClass_UAnimBlueprint_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_rightTopHandAnimationClass_MetaData), NewProp_rightTopHandAnimationClass_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_walkHandStretchCurve = { "walkHandStretchCurve", nullptr, (EPropertyFlags)0x0010000000010005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, walkHandStretchCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_walkHandStretchCurve_MetaData), NewProp_walkHandStretchCurve_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_attackHandStretchCurve = { "attackHandStretchCurve", nullptr, (EPropertyFlags)0x0010000000010005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, attackHandStretchCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_attackHandStretchCurve_MetaData), NewProp_attackHandStretchCurve_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_handAngularLimitCurve = { "handAngularLimitCurve", nullptr, (EPropertyFlags)0x0010000000010005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, handAngularLimitCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_handAngularLimitCurve_MetaData), NewProp_handAngularLimitCurve_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_effectActorsArr_Inner = { "effectActorsArr", nullptr, (EPropertyFlags)0x0004000000000000, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UClass, Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_effectActorsArr = { "effectActorsArr", nullptr, (EPropertyFlags)0x0014000000010005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, effectActorsArr), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_effectActorsArr_MetaData), NewProp_effectActorsArr_MetaData) };
void Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_bIsHandsShowed_SetBit(void* Obj)
{
	((AOctopusBackpackActor*)Obj)->bIsHandsShowed = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_bIsHandsShowed = { "bIsHandsShowed", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AOctopusBackpackActor), &Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_bIsHandsShowed_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsHandsShowed_MetaData), NewProp_bIsHandsShowed_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_sectionCount = { "sectionCount", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, sectionCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_sectionCount_MetaData), NewProp_sectionCount_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_sphereRadius = { "sphereRadius", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, sphereRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_sphereRadius_MetaData), NewProp_sphereRadius_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_sphereSpacer = { "sphereSpacer", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, sphereSpacer), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_sphereSpacer_MetaData), NewProp_sphereSpacer_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_sphereMass = { "sphereMass", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, sphereMass), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_sphereMass_MetaData), NewProp_sphereMass_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_junctionCount = { "junctionCount", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, junctionCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_junctionCount_MetaData), NewProp_junctionCount_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_junctionEndSpace = { "junctionEndSpace", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, junctionEndSpace), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_junctionEndSpace_MetaData), NewProp_junctionEndSpace_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_maxBrokenHandDistance = { "maxBrokenHandDistance", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, maxBrokenHandDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_maxBrokenHandDistance_MetaData), NewProp_maxBrokenHandDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_maxBrokenHandDistanceSquared = { "maxBrokenHandDistanceSquared", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, maxBrokenHandDistanceSquared), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_maxBrokenHandDistanceSquared_MetaData), NewProp_maxBrokenHandDistanceSquared_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_physDamping_ = { "physDamping_", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, physDamping_), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_physDamping__MetaData), NewProp_physDamping__MetaData) };
void Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_bIsActivateBackpack_SetBit(void* Obj)
{
	((AOctopusBackpackActor*)Obj)->bIsActivateBackpack = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_bIsActivateBackpack = { "bIsActivateBackpack", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AOctopusBackpackActor), &Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_bIsActivateBackpack_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsActivateBackpack_MetaData), NewProp_bIsActivateBackpack_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_sphereDistanceLoc = { "sphereDistanceLoc", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, sphereDistanceLoc), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_sphereDistanceLoc_MetaData), NewProp_sphereDistanceLoc_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_backpackComponent = { "backpackComponent", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOctopusBackpackActor, backpackComponent), Z_Construct_UClass_UOctopusBackpackComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_backpackComponent_MetaData), NewProp_backpackComponent_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AOctopusBackpackActor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_sceneComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_LeftBottomHandStartMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_RightBottomHandStartMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_LeftTopHandStartMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_RightTopHandStartMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_LeftBottomHandFallingArrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_RightBottomHandFallingArrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_LeftTopHandFallingArrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_RightTopHandFallingArrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_LeftBottomHandStartArrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_RightBottomHandStartArrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_LeftTopHandStartArrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_RightTopHandStartArrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_LeftBottomHandGrabArrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_RightBottomHandGrabArrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_LeftTopHandGrabArrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_RightTopHandGrabArrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_LeftBottomHandWalkArrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_RightBottomHandWalkArrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_LeftTopHandWalkArrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_RightTopHandWalkArrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_LeftBottomHandWalkGrabArrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_RightBottomHandWalkGrabArrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_LeftTopHandWalkGrabArrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_RightTopHandWalkGrabArrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_tentaclesArr_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_tentaclesArr,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_tentaclesStaticMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_tentaclesBigStaticMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_handSkeletalMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_junctionStaticMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_leftBottomHandAnimationClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_rightBottomHandAnimationClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_leftTopHandAnimationClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_rightTopHandAnimationClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_walkHandStretchCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_attackHandStretchCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_handAngularLimitCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_effectActorsArr_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_effectActorsArr,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_bIsHandsShowed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_sectionCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_sphereRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_sphereSpacer,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_sphereMass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_junctionCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_junctionEndSpace,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_maxBrokenHandDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_maxBrokenHandDistanceSquared,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_physDamping_,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_bIsActivateBackpack,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_sphereDistanceLoc,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOctopusBackpackActor_Statics::NewProp_backpackComponent,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AOctopusBackpackActor_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AOctopusBackpackActor_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_OctopusBackpack,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AOctopusBackpackActor_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AOctopusBackpackActor_Statics::ClassParams = {
	&AOctopusBackpackActor::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AOctopusBackpackActor_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AOctopusBackpackActor_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AOctopusBackpackActor_Statics::Class_MetaDataParams), Z_Construct_UClass_AOctopusBackpackActor_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AOctopusBackpackActor()
{
	if (!Z_Registration_Info_UClass_AOctopusBackpackActor.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AOctopusBackpackActor.OuterSingleton, Z_Construct_UClass_AOctopusBackpackActor_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AOctopusBackpackActor.OuterSingleton;
}
template<> OCTOPUSBACKPACK_API UClass* StaticClass<AOctopusBackpackActor>()
{
	return AOctopusBackpackActor::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AOctopusBackpackActor);
AOctopusBackpackActor::~AOctopusBackpackActor() {}
// End Class AOctopusBackpackActor

// Begin Registration
struct Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusBackpackActor_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AOctopusBackpackActor, AOctopusBackpackActor::StaticClass, TEXT("AOctopusBackpackActor"), &Z_Registration_Info_UClass_AOctopusBackpackActor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AOctopusBackpackActor), 2884007565U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusBackpackActor_h_2744605947(TEXT("/Script/OctopusBackpack"),
	Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusBackpackActor_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusBackpackActor_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
