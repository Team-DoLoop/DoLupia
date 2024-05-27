// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ProjectDGameInstance.generated.h"

/**
 * 
 */

struct FPlayerSkillData;
UCLASS()
class PROJECTD_API UProjectDGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UProjectDGameInstance();

	virtual void Init() override;
	FPlayerSkillData* GetPlayerSkillData(int32 SkillID);

private:
	UPROPERTY()
	class UDataTable* PlayerSkillTable;

};
