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
	IDLE UMETA(DisplayName = "Idle"),
	MOVE UMETA(DisplayName = "Move"),
	
	ATTACK UMETA(DisplayName = "Attack"),
	DAMAGE UMETA(DisplayName = "Damage"),
	EVASION UMETA(DisplayName = "Evasion"),

	TALK_NPC UMETA(DisplayName = "TalkNPC"),
	
	DIE UMETA(DisplayName = "Die"),
};


UCLASS()
class PROJECTD_API UPlayerStateBase : public UObject
{
	GENERATED_BODY()
	
};
