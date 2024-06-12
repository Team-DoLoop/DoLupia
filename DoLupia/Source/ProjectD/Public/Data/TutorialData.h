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
	ITEM_OIL UMETA(DisplayName = "Item_Oil"),							// 기름
	ITEM_COOL_WATER UMETA(DisplayName = "Item_Cool_Water"),				// 냉각수
	ITEM_SKILL_UPGRADE UMETA(DisplayName = "Item_Skill_Upgrade"),		// 스킬 업그레이드
	FULL_HIT_GAUGE UMETA(DisplayName = "Full_Hit_Gauge"),				// MP가 꽉 찬 경우
};

UENUM(BlueprintType)
enum class ETutoItemType : uint8
{
	NONE UMETA(DisplayName = "None"),
	OIL UMETA(DisplayName = "Oil"),								// 기름
	COOL_WATER UMETA(DisplayName = "Cool_Water"),				// 냉각수
	BATTERY_RED_Q UMETA(DisplayName = "Battery_Red_Q"),			// 스킬 업그레이드
	BATTERY_RED_W UMETA(DisplayName = "Battery_Red_Q"),	
	BATTERY_YELLOW_Q UMETA(DisplayName = "Battery_Yellow_Q"),
	BATTERY_YELLOW_W UMETA(DisplayName = "Battery_Yellow_W"),
	BATTERY_BLUE_Q UMETA(DisplayName = "Battery_Blue_Q"),
	BATTERY_BLUE_W UMETA(DisplayName = "Battery_Blue_W"),
};

USTRUCT(BlueprintType)
struct FTutorialWidgetData
{
	GENERATED_BODY()
	
	// 설명 텍스트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ExplainText;
};


USTRUCT(BlueprintType)
struct FTutorialItem
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsGiveItem;										// 아이템 제공 튜토리얼인지
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETutoItemType GiveItem;									// 어느 아이템을 제공하는지

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GiveItemQuantity;									// 몇개 제공하는지
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

	// 다음 지문
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NextIndex;

	// 아이템 지급 데이터
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTutorialItem TutorialItem;
	
	// 위젯 관련 데이터
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTutorialWidgetData TutorialWidgetData;

	// 퀘스트 관련 데이터
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTutorialQuest TutorialQuest;
};
