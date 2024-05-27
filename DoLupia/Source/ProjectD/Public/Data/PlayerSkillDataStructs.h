#pragma once

#include "CoreMinimal.h"
#include "Common/UseColor.h"
#include "Engine/DataTable.h"
#include "PlayerSkillDataStructs.generated.h"

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	NONE UMETA(DisplayName = "None"),
	MELEE UMETA(DisplayName = "Melee"),
	RANGED UMETA(DisplayName = "Ranged"),
	SWAP UMETA(DisplayName = "Swap"),
	ULT UMETA(DisplayName = "Ult"),
};

USTRUCT(BlueprintType)
struct FPlayerSkillData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EUseColor SkillColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillType SkillType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* SkillThumnail;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* SkillMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SkillDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillCoolTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillDamage;
};