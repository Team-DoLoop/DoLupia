// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ProjectDGameInstance.generated.h"

/**
 * 
 */

enum class EUseColor : uint8;
struct FPlayerSkillData;
UCLASS()
class PROJECTD_API UProjectDGameInstance : public UGameInstance
{
	GENERATED_BODY()


	// <------------------ Player Skill ------------------>
public:
	UProjectDGameInstance();

	virtual void Init() override;
	void InitCanUseColor();
	
	FPlayerSkillData* GetPlayerSkillData(int32 SkillID);
	FORCEINLINE TMap<EUseColor, bool> GetCanUseColor(){return CanUseColor;}
	FORCEINLINE void SetCanUseColor(EUseColor _Color, bool bCanUse) {CanUseColor[_Color] = bCanUse;}
	

private:
	UPROPERTY()
	class UDataTable* PlayerSkillTable;

	UPROPERTY()
	TMap<EUseColor, bool> CanUseColor;



public:

};
