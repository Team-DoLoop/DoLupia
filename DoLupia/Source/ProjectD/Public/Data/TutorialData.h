#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "TutorialData.generated.h"

UENUM(BlueprintType)
enum class EExplainType : uint8
{
	NONE UMETA(DisplayName = "None"),
	MOVE UMETA(DisplayName = "Move"),									// 이동
	ATTACK UMETA(DisplayName = "Attack"),								// 공격(전투)
	SKILL UMETA(DisplayName = "Skill"),									// 스킬
	ITEM_COOL_WATER UMETA(DisplayName = "Item_Cool_Water"),				// 냉각수
	ITEM_SKILL_UPGRADE UMETA(DisplayName = "Item_Skill_Upgrade"),		// 스킬 업그레이드
	FULL_HIT_GAUGE UMETA(DisplayName = "Full_Hit_Gauge"),				// MP가 꽉 찬 경우
};


USTRUCT(BlueprintType)
struct FTutorialWidgetData
{
	GENERATED_BODY()

	// 설명 텍스트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ExplainText;

	// 위젯 사라질 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FadeOutTime;
};


USTRUCT(BlueprintType)
struct FTutorialQuest
{
	GENERATED_BODY()

	// 퀘스트 관련인지
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsQuest;

	// 어느 퀘스트랑인지
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 QuestID;
};


USTRUCT(BlueprintType)
struct FTutorialData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EExplainType ExplainType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ExplainIndex;
	
	// 위젯 관련 데이터
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTutorialWidgetData TutorialWidgetData;

	// 퀘스트 관련 데이터
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTutorialQuest TutorialQuest;
};
