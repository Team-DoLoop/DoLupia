// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStructs.generated.h"


enum class EUseColor : uint8;
class UNiagaraSystem;

UENUM(BlueprintType)
enum class EItemQuality : uint8
{
	Shoddy UMETA(DisplayName = "Shoddy"),
	Common UMETA(DisplayName = "Common"),
	Quality UMETA(DisplayName = "Quality"),
	Masterwork UMETA(DisplayName = "Masterwork"),
	Grandmaster UMETA(DisplayName = "Grandmaster")
};


UENUM(BlueprintType)
enum class EItemType : uint8
{
	Head UMETA( DisplayName = "Head" ),
	Top UMETA(DisplayName = "Top"),
	Pants UMETA( DisplayName = "Pants"),
	Shoes UMETA( DisplayName = "Shoes"),
	Shield UMETA(DisplayName = "Shield"),
	Weapon UMETA( DisplayName = "Weapon" ) ,
	Spell UMETA(DisplayName = "Spell"),
	Consumable UMETA(DisplayName = "Consumable"),
	Quest UMETA(DisplayName = "Quest"),
	Mundane UMETA(DisplayName = "Mundane"),
	ItemType_End,

};

UENUM( BlueprintType )
enum class ESkillAttribute : uint8
{
	NONE UMETA(DisplayName = "None"),
	CYLINDRICAL UMETA(DisplayName = "Cylindrical"),
	PRISMATIC UMETA( DisplayName = "Prismatic" ),
};

USTRUCT()
struct FItemStatistics
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY( EditAnywhere, Category = "Level")
	int32 ItemLevel;

	UPROPERTY( EditAnywhere , Category = "Equipment" )
	float DefenseIncreaseAmount;

	UPROPERTY( EditAnywhere , Category = "Equipment" )
	float DamageIncreaseAmount;

	UPROPERTY( EditAnywhere, Category = "Item")
	int32 ItemSkillID;
	
	UPROPERTY( EditAnywhere , Category = "Item" )
	float HealthIncreaseAmount;

	UPROPERTY(EditAnywhere , Category = "Equipment" )
	float ArmorRating;

	UPROPERTY(EditAnywhere , Category = "Equipment" )
	float DamageValue;

	UPROPERTY( EditAnywhere , Category = "Item" )
	float HealthValue;

	UPROPERTY( EditAnywhere , Category = "Item" )
	float ManaValue;

	UPROPERTY(EditAnywhere , Category = "Store" )
	float RestorationAmout;

	UPROPERTY(EditAnywhere, Category = "Store" )
	float SellValue;

	UPROPERTY( EditAnywhere , Category = "Item" )
	FVector MeshScale = FVector(1.0, 1.0, 1.0);

	UPROPERTY( EditAnywhere , Category = "Item" )
	float MassScale = 20.f;

	UPROPERTY( EditAnywhere , Category = "Item" )
	float GravityScale = 0.77f;


};

USTRUCT()
struct FItemConsumableStatistics
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY( EditAnywhere , Category = "Item" )
	float HealthValue;
};

USTRUCT()
struct FItemTextData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FText Name;

	UPROPERTY(EditAnywhere)
	FText Description;

	UPROPERTY(EditAnywhere)
	FText InteractionText;

	UPROPERTY(EditAnywhere)
	FText UsageText;
};

USTRUCT()
struct FItemNumericData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	float Weight;

	UPROPERTY(EditAnywhere)
	int32 MaxStackSize;

	UPROPERTY(EditAnywhere)
	bool bIsStackable;
};

USTRUCT()
struct FItemAssetData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere)
	UMaterialInstance* IconMaterial;

	UPROPERTY(EditAnywhere)
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere)
	UStaticMesh* SubMesh;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* EquipeedItemEffect;
	
	UPROPERTY( EditAnywhere )
	USoundWave* ItemUseSFX;
};

USTRUCT()
struct FItemMaterialBackGround
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY( EditAnywhere , Category = "Materials" )
	float BoxFillOpacity = 1.0f;

	UPROPERTY( EditAnywhere , Category = "Materials" )
	float BoxScale = 0.85f;

	UPROPERTY( EditAnywhere , Category = "Materials" )
	float FrameThickness = 100.f;

	UPROPERTY( EditAnywhere , Category = "Materials" )
	float GlowMax = 0.12;

	UPROPERTY( EditAnywhere , Category = "Materials" )
	float GlowMin = 0.006f;

	UPROPERTY( EditAnywhere , Category = "Materials" )
	float NoiseIntensity = 0.02f;
};

USTRUCT()
struct FItemMaterialGradient
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY( EditAnywhere , Category = "Materials" )
	FLinearColor Color1 = FLinearColor( 0.0f , 0.0f , 0.0f , 0.f );;

	UPROPERTY( EditAnywhere , Category = "Materials" )
	FLinearColor Color2 = FLinearColor( 0.584201f , 0.189196f , 0.013782f, 0.0f );

	UPROPERTY( EditAnywhere , Category = "Materials" )
	FLinearColor Color3 = FLinearColor( 1.f , 0.767103, 0.472022f , 0.0f );

	UPROPERTY( EditAnywhere , Category = "Materials" )
	FLinearColor Color3_Active = FLinearColor( 1.f , 0.702795f, 0.233507f , 0.0f );

	UPROPERTY( EditAnywhere , Category = "Materials" )
	float Glow_max = 0.75f;

	UPROPERTY( EditAnywhere , Category = "Materials" )
	float Glow_min = 0.0f;

	UPROPERTY( EditAnywhere , Category = "Materials" )
	float NoiseIntensity = 0.05f;

	UPROPERTY( EditAnywhere , Category = "Materials" )
	float PosColor1 = 0.0f;

	UPROPERTY( EditAnywhere , Category = "Materials" )
	float PosColor2 = 0.3f;

	UPROPERTY( EditAnywhere , Category = "Materials" )
	float PosColor3 = 1.0f;

	UPROPERTY( EditAnywhere , Category = "Materials" )
	float Size = 0.36f;

	UPROPERTY( EditAnywhere , Category = "Materials" )
	FLinearColor NoisePanningSpeed = FLinearColor( 0.03f, 0.04f, 0.0f, 0.0f );
};

USTRUCT()
struct FItemMaterialFrame
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY( EditAnywhere , Category = "Materials" )
	FLinearColor BaseColor = FLinearColor( 0.424075f , 0.59679f , 1.0f , 0.0f );

	UPROPERTY( EditAnywhere , Category = "Materials" )
	float AlphaIntensity = 1.0f;

	UPROPERTY( EditAnywhere , Category = "Materials" )
	float Contrast = 2.0f;

	UPROPERTY( EditAnywhere , Category = "Materials" )
	float Speed = -0.2f;

	UPROPERTY( EditAnywhere , Category = "Materials" )
	float SubDivisions = 4.0f;

	UPROPERTY( EditAnywhere , Category = "Materials" )
	FLinearColor HoveredGradientColor = FLinearColor( 0.559847, 0.946807, 1.0f , 0.f );
};


USTRUCT()
struct FItemMaterialTexture
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY( EditAnywhere , Category = "Materials" )
	float HoveredAdditinal = 0.1f;

	UPROPERTY( EditAnywhere , Category = "Materials" )
	FLinearColor Offset = FLinearColor( 0.0f , 0.0f , 0.0f , 0.f );

	UPROPERTY( EditAnywhere , Category = "Materials" )
	FLinearColor Offset_Active = FLinearColor(0.03f, 0.04f, 0.0f, 0.f);

	UPROPERTY( EditAnywhere , Category = "Materials" )
	float Scale = 0.7f;

	UPROPERTY( EditAnywhere , Category = "Materials" )
	float Scale_Active = 0.9f;
};

USTRUCT()
struct FItemMaterial
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY( EditAnywhere , Category = "Materials" )
	FItemMaterialBackGround ItemMaterialBackGround;

	UPROPERTY( EditAnywhere , Category = "Materials" )
	FItemMaterialGradient ItemMaterialGradient;

	UPROPERTY( EditAnywhere , Category = "Materials" )
	FItemMaterialTexture ItemMaterialTexture;

	UPROPERTY( EditAnywhere , Category = "Materials" )
	FItemMaterialFrame ItemMaterialFrame;
};


USTRUCT()
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FName ID;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemQuality ItemQuality;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemStatistics ItemStatistics;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemTextData TextData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemNumericData NumericData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemAssetData AssetData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	ESkillAttribute SkillAttribute;

	UPROPERTY( EditAnywhere , Category = "Item Data" )
	FItemMaterial ItemMaterial;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EUseColor ItemSkillColor;
};