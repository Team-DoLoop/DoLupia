// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerStateBase.generated.h"


/**
 * Manage Player State
 */


UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	IDLE UMETA(DisplayName = "Idle"),				// 대기
	MOVE UMETA(DisplayName = "Move"),				// 이동
	EVASION UMETA(DisplayName = "Evasion"),			// 회피
	
	ATTACK UMETA(DisplayName = "Attack"),			// 공격
	DAMAGE UMETA(DisplayName = "Damage"),			// 피격
	LYING UMETA(DisplayName = "Lying"),				// 눕는 공격 피격

	TALK_NPC UMETA(DisplayName = "TalkNPC"),		// NPC 대화
	
	DIE UMETA(DisplayName = "Die"),					// 죽기
};

UENUM(BlueprintType)
enum class EPlayerWeaponState : uint8
{
	UNARMED UMETA(DisplayName = "Unarmed"),			// 비무장
	SWORD UMETA(DisplayName = "Sword"),				// 대검
};

UCLASS()
class PROJECTD_API UPlayerStateBase : public UObject
{
	GENERATED_BODY()
	
};
