#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "TutorialData.generated.h"

UENUM(BlueprintType)
enum class EExplainType : uint8
{
	NONE UMETA(DisplayName = "None"),
	FULL_HIT_GAUGE UMETA(DisplayName = "Full_Hit_Gauge"),
};


USTRUCT(BlueprintType)
struct FTutorialData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ExplainText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FadeOutTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsQuest;
};
