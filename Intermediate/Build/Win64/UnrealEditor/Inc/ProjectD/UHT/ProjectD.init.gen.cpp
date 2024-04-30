// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeProjectD_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_ProjectD;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_ProjectD()
	{
		if (!Z_Registration_Info_UPackage__Script_ProjectD.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/ProjectD",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0xB622C1B4,
				0x5B36CB73,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_ProjectD.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_ProjectD.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_ProjectD(Z_Construct_UPackage__Script_ProjectD, TEXT("/Script/ProjectD"), Z_Registration_Info_UPackage__Script_ProjectD, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xB622C1B4, 0x5B36CB73));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
