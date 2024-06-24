// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackType.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	BASIC UMETA(DisplayName = "Basic"),				// 기본 공격
	LYING UMETA(DisplayName = "Lying"),				// 눕히는 공격
};

UENUM(BlueprintType)
enum class EEffectAttackType : uint8
{
	NONE = 0 UMETA(DisplyaName = "None"),
	BLEED = 1 UMETA(DisplayName = "Bleed"),
	POISON = 2 UMETA(DisplayName = "Poison"),
	FIRE = 3 UMETA(DisplayName = "Fire"),
	ELECTRIC = 4 UMETA(DisplayName = "Electric")
};

UCLASS()
class PROJECTD_API UAttackType : public UObject
{
	GENERATED_BODY()
	
};
