// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ProjectDGameMode.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef PROJECTD_ProjectDGameMode_generated_h
#error "ProjectDGameMode.generated.h already included, missing '#pragma once' in ProjectDGameMode.h"
#endif
#define PROJECTD_ProjectDGameMode_generated_h

#define FID_DoLupia_Source_ProjectD_ProjectDGameMode_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAProjectDGameMode(); \
	friend struct Z_Construct_UClass_AProjectDGameMode_Statics; \
public: \
	DECLARE_CLASS(AProjectDGameMode, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProjectD"), PROJECTD_API) \
	DECLARE_SERIALIZER(AProjectDGameMode)


#define FID_DoLupia_Source_ProjectD_ProjectDGameMode_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AProjectDGameMode(AProjectDGameMode&&); \
	AProjectDGameMode(const AProjectDGameMode&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(PROJECTD_API, AProjectDGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AProjectDGameMode); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AProjectDGameMode) \
	PROJECTD_API virtual ~AProjectDGameMode();


#define FID_DoLupia_Source_ProjectD_ProjectDGameMode_h_9_PROLOG
#define FID_DoLupia_Source_ProjectD_ProjectDGameMode_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_DoLupia_Source_ProjectD_ProjectDGameMode_h_12_INCLASS_NO_PURE_DECLS \
	FID_DoLupia_Source_ProjectD_ProjectDGameMode_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> PROJECTD_API UClass* StaticClass<class AProjectDGameMode>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_DoLupia_Source_ProjectD_ProjectDGameMode_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
