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
	IDLE UMETA(DisplayName = "Idle"),							// 대기
	MOVE UMETA(DisplayName = "Move"),							// 이동
	EVASION UMETA(DisplayName = "Evasion"),						// 회피
	
	ATTACK_ONLY UMETA(DisplayName = "AttackOnly"),				// 공격(아무것도 못함)
	ATTACK_WITH UMETA(DisplayName = "AttackWith"),				// 동작 가능
	DAMAGE UMETA(DisplayName = "Damage"),						// 피격
	LYING UMETA(DisplayName = "Lying"),							// 눕는 공격 피격
	GRAB UMETA(DisplayName = "Grab"),							// 보스 몬스터에게 잡기당한 상태

	TALK_NPC UMETA(DisplayName = "TalkNPC"),					// NPC 대화
	
	DIE UMETA(DisplayName = "Die"),								// 죽기
};

UENUM(BlueprintType)
enum class EPlayerWeaponState : uint8
{
	UNARMED UMETA(DisplayName = "Unarmed"),						// 비무장
	SWORD UMETA(DisplayName = "Sword"),							// 대검
};

UENUM(BlueprintType)
enum class EPlayerShieldState : uint8
{
	NONE UMETA(DisplayName = "None"),							// 쉴드 X
	SHIELD UMETA(DisplayName = "Shield"),						// 쉴드 O
};


UCLASS()
class PROJECTD_API UPlayerStateBase : public UObject
{
	GENERATED_BODY()
	
};
