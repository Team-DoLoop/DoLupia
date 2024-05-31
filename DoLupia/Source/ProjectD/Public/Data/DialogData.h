// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DialogData.generated.h"

USTRUCT( BlueprintType )
struct FDialogueData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY( EditAnywhere , BlueprintReadWrite )
    FString NPCName;

    UPROPERTY( EditAnywhere , BlueprintReadWrite )
    FString Speaker;

    UPROPERTY( EditAnywhere , BlueprintReadWrite )
    FString DialogueText;

    UPROPERTY( EditAnywhere , BlueprintReadWrite )
    int32 NextID;

    UPROPERTY( EditAnywhere , BlueprintReadWrite )
    bool bTriggersQuest;  // 퀘스트 트리거 여부
};

/**
 * 
 */
UCLASS()
class PROJECTD_API UDialogData : public UDataTable
{
	GENERATED_BODY()
	
};
