// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ProjectDPlayerController.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef PROJECTD_ProjectDPlayerController_generated_h
#error "ProjectDPlayerController.generated.h already included, missing '#pragma once' in ProjectDPlayerController.h"
#endif
#define PROJECTD_ProjectDPlayerController_generated_h

#define FID_DoLupia_Source_ProjectD_ProjectDPlayerController_h_20_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAProjectDPlayerController(); \
	friend struct Z_Construct_UClass_AProjectDPlayerController_Statics; \
public: \
	DECLARE_CLASS(AProjectDPlayerController, APlayerController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProjectD"), NO_API) \
	DECLARE_SERIALIZER(AProjectDPlayerController)


#define FID_DoLupia_Source_ProjectD_ProjectDPlayerController_h_20_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AProjectDPlayerController(AProjectDPlayerController&&); \
	AProjectDPlayerController(const AProjectDPlayerController&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AProjectDPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AProjectDPlayerController); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AProjectDPlayerController) \
	NO_API virtual ~AProjectDPlayerController();


#define FID_DoLupia_Source_ProjectD_ProjectDPlayerController_h_17_PROLOG
#define FID_DoLupia_Source_ProjectD_ProjectDPlayerController_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_DoLupia_Source_ProjectD_ProjectDPlayerController_h_20_INCLASS_NO_PURE_DECLS \
	FID_DoLupia_Source_ProjectD_ProjectDPlayerController_h_20_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> PROJECTD_API UClass* StaticClass<class AProjectDPlayerController>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_DoLupia_Source_ProjectD_ProjectDPlayerController_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
