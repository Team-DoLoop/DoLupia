// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStructs.generated.h"


enum class EUseColor : uint8;

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
	Fire UMETA( DisplayName = "Fire" ) ,
	Water UMETA( DisplayName = "Water" ) ,
	Ground UMETA( DisplayName = "Ground" ) ,
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
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere)
	UStaticMesh* SubMesh;
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

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EUseColor ItemSkillColor;
};