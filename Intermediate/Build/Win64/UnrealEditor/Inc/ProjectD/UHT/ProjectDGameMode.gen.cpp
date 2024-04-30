// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ProjectD/ProjectDGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeProjectDGameMode() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
PROJECTD_API UClass* Z_Construct_UClass_AProjectDGameMode();
PROJECTD_API UClass* Z_Construct_UClass_AProjectDGameMode_NoRegister();
UPackage* Z_Construct_UPackage__Script_ProjectD();
// End Cross Module References

// Begin Class AProjectDGameMode
void AProjectDGameMode::StaticRegisterNativesAProjectDGameMode()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AProjectDGameMode);
UClass* Z_Construct_UClass_AProjectDGameMode_NoRegister()
{
	return AProjectDGameMode::StaticClass();
}
struct Z_Construct_UClass_AProjectDGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "ProjectDGameMode.h" },
		{ "ModuleRelativePath", "ProjectDGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AProjectDGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AProjectDGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_ProjectD,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AProjectDGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AProjectDGameMode_Statics::ClassParams = {
	&AProjectDGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008802ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AProjectDGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_AProjectDGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AProjectDGameMode()
{
	if (!Z_Registration_Info_UClass_AProjectDGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AProjectDGameMode.OuterSingleton, Z_Construct_UClass_AProjectDGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AProjectDGameMode.OuterSingleton;
}
template<> PROJECTD_API UClass* StaticClass<AProjectDGameMode>()
{
	return AProjectDGameMode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AProjectDGameMode);
AProjectDGameMode::~AProjectDGameMode() {}
// End Class AProjectDGameMode

// Begin Registration
struct Z_CompiledInDeferFile_FID_DoLupia_Source_ProjectD_ProjectDGameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AProjectDGameMode, AProjectDGameMode::StaticClass, TEXT("AProjectDGameMode"), &Z_Registration_Info_UClass_AProjectDGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AProjectDGameMode), 1289668637U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_DoLupia_Source_ProjectD_ProjectDGameMode_h_3212627291(TEXT("/Script/ProjectD"),
	Z_CompiledInDeferFile_FID_DoLupia_Source_ProjectD_ProjectDGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_DoLupia_Source_ProjectD_ProjectDGameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
