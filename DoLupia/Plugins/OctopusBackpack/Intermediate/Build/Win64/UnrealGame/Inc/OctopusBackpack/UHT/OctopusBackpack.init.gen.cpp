// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeOctopusBackpack_init() {}
	OCTOPUSBACKPACK_API UFunction* Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusFlyingMode__DelegateSignature();
	OCTOPUSBACKPACK_API UFunction* Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusReturnMovement__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_OctopusBackpack;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_OctopusBackpack()
	{
		if (!Z_Registration_Info_UPackage__Script_OctopusBackpack.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusFlyingMode__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_UOctopusBackpackComponent_OctopusReturnMovement__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/OctopusBackpack",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x56351D0C,
				0x196DDF58,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_OctopusBackpack.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_OctopusBackpack.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_OctopusBackpack(Z_Construct_UPackage__Script_OctopusBackpack, TEXT("/Script/OctopusBackpack"), Z_Registration_Info_UPackage__Script_OctopusBackpack, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x56351D0C, 0x196DDF58));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
