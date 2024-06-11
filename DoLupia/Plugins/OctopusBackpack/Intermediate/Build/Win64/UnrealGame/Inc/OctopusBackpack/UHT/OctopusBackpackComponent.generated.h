// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "OctopusBackpackComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
class UObject;
struct FHitResult;
#ifdef OCTOPUSBACKPACK_OctopusBackpackComponent_generated_h
#error "OctopusBackpackComponent.generated.h already included, missing '#pragma once' in OctopusBackpackComponent.h"
#endif
#define OCTOPUSBACKPACK_OctopusBackpackComponent_generated_h

#define FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusBackpackComponent_h_16_DELEGATE \
static void FOctopusReturnMovement_DelegateWrapper(const FMulticastScriptDelegate& OctopusReturnMovement, FVector inScale);


#define FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusBackpackComponent_h_17_DELEGATE \
static void FOctopusFlyingMode_DelegateWrapper(const FMulticastScriptDelegate& OctopusFlyingMode, bool bIsActivated);


#define FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusBackpackComponent_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execThrowAll); \
	DECLARE_FUNCTION(execDropAll); \
	DECLARE_FUNCTION(execThrow); \
	DECLARE_FUNCTION(execDrop); \
	DECLARE_FUNCTION(execIsComponentGrabbed); \
	DECLARE_FUNCTION(execAttackHand); \
	DECLARE_FUNCTION(execAttack); \
	DECLARE_FUNCTION(execRegisterOctopusBackpack); \
	DECLARE_FUNCTION(execOctopusBackpackBattleMode); \
	DECLARE_FUNCTION(execOctopusBackpackFlyingMode); \
	DECLARE_FUNCTION(execSetMovementDirection);


#define FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusBackpackComponent_h_14_CALLBACK_WRAPPERS
#define FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusBackpackComponent_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUOctopusBackpackComponent(); \
	friend struct Z_Construct_UClass_UOctopusBackpackComponent_Statics; \
public: \
	DECLARE_CLASS(UOctopusBackpackComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/OctopusBackpack"), NO_API) \
	DECLARE_SERIALIZER(UOctopusBackpackComponent)


#define FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusBackpackComponent_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UOctopusBackpackComponent(UOctopusBackpackComponent&&); \
	UOctopusBackpackComponent(const UOctopusBackpackComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UOctopusBackpackComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UOctopusBackpackComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UOctopusBackpackComponent) \
	NO_API virtual ~UOctopusBackpackComponent();


#define FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusBackpackComponent_h_11_PROLOG
#define FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusBackpackComponent_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusBackpackComponent_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusBackpackComponent_h_14_CALLBACK_WRAPPERS \
	FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusBackpackComponent_h_14_INCLASS_NO_PURE_DECLS \
	FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusBackpackComponent_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> OCTOPUSBACKPACK_API UClass* StaticClass<class UOctopusBackpackComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusBackpackComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
