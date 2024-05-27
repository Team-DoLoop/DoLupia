#pragma once

#include "CoreMinimal.h"
#include "Common/UseColor.h"
#include "Engine/DataTable.h"
#include "PlayerSkillDataStructs.generated.h"

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	MELEE UMETA(DisplayName = "Melee"),
	RANGED UMETA(DisplayName = "Ranged"),
	SWAP UMETA(DisplayName = "Swap"),
	ULT UMETA(DisplayName = "Ult"),
};

USTRUCT(BlueprintType)
struct FPlayerSkillData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FPlayerSkillData() : ID(1), SkillLevel(1), SkillCost(10), SkillCoolTime(5), SkillDamage(10){}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ID;
	
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