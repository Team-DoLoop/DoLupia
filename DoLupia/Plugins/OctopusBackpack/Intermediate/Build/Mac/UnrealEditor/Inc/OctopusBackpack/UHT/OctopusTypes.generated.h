// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "OctopusTypes.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef OCTOPUSBACKPACK_OctopusTypes_generated_h
#error "OctopusTypes.generated.h already included, missing '#pragma once' in OctopusTypes.h"
#endif
#define OCTOPUSBACKPACK_OctopusTypes_generated_h

#define FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusTypes_h_57_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FOctoHandStatus_Statics; \
	OCTOPUSBACKPACK_API static class UScriptStruct* StaticStruct();


template<> OCTOPUSBACKPACK_API UScriptStruct* StaticStruct<struct FOctoHandStatus>();

#define FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusTypes_h_111_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FOctoTentaclesStruct_Statics; \
	OCTOPUSBACKPACK_API static class UScriptStruct* StaticStruct();


template<> OCTOPUSBACKPACK_API UScriptStruct* StaticStruct<struct FOctoTentaclesStruct>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_OctopusBackpack_Source_OctopusBackpack_Public_OctopusTypes_h


#define FOREACH_ENUM_EOCTO_MOVE(op) \
	op(EOcto_Move::NONE) \
	op(EOcto_Move::FORWARD) \
	op(EOcto_Move::BACKWARD) \
	op(EOcto_Move::TOP) \
	op(EOcto_Move::BOTTOM) \
	op(EOcto_Move::LEFT) \
	op(EOcto_Move::RIGHT) 

enum class EOcto_Move : uint8;
template<> struct TIsUEnumClass<EOcto_Move> { enum { Value = true }; };
template<> OCTOPUSBACKPACK_API UEnum* StaticEnum<EOcto_Move>();

#define FOREACH_ENUM_EOCTOHANDACTION(op) \
	op(EOctoHandAction::IDLE) \
	op(EOctoHandAction::MOVE_TO_ATTACH_POINT) \
	op(EOctoHandAction::ATTACHED) \
	op(EOctoHandAction::GRABBED_RETURN) \
	op(EOctoHandAction::ATTACKS) \
	op(EOctoHandAction::RETURNS) \
	op(EOctoHandAction::GRABBED) \
	op(EOctoHandAction::THROW) \
	op(EOctoHandAction::FALLING) \
	op(EOctoHandAction::SHOW_HIDE) 

enum class EOctoHandAction : uint8;
template<> struct TIsUEnumClass<EOctoHandAction> { enum { Value = true }; };
template<> OCTOPUSBACKPACK_API UEnum* StaticEnum<EOctoHandAction>();

#define FOREACH_ENUM_EOCTO_HAND(op) \
	op(EOcto_Hand::LEFT_BOTTOM) \
	op(EOcto_Hand::RIGHT_BOTTOM) \
	op(EOcto_Hand::LEFT_TOP) \
	op(EOcto_Hand::RIGHT_TOP) 

enum class EOcto_Hand : uint8;
template<> struct TIsUEnumClass<EOcto_Hand> { enum { Value = true }; };
template<> OCTOPUSBACKPACK_API UEnum* StaticEnum<EOcto_Hand>();

#define FOREACH_ENUM_EOCTO_HANDPOINT(op) \
	op(EOcto_HandPoint::WALK_ORIGIN) \
	op(EOcto_HandPoint::WALK_GRAB_ORIGIN) \
	op(EOcto_HandPoint::FLY_ORIGIN) \
	op(EOcto_HandPoint::FALLING_ORIGIN) \
	op(EOcto_HandPoint::FLY_GRAB_ORIGIN) 

enum class EOcto_HandPoint : uint8;
template<> struct TIsUEnumClass<EOcto_HandPoint> { enum { Value = true }; };
template<> OCTOPUSBACKPACK_API UEnum* StaticEnum<EOcto_HandPoint>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
