// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerSkillWidget.generated.h"

struct FPlayerSkillData;
/**
 * 
 */
class UPlayerSkillSlotWidget;
class UProjectDGameInstance;
UCLASS()
class PROJECTD_API UPlayerSkillWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized ( ) override;
	
private:
	UProjectDGameInstance* GI;
	
private:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UHorizontalBox* SkillBox;

	UPROPERTY ( EditDefaultsOnly )
	TSubclassOf<class UPlayerSkillSlotWidget> PlayerSkillSlotFactory;

	UPROPERTY ( VisibleDefaultsOnly )
	TArray<UPlayerSkillSlotWidget*> PlayerSkillSlotArray;
	
public:
	void InitSkillSlot();
	void UpdateSkillUI(int32 SlotIndex, FPlayerSkillData* PlayerSkillData);
	void UpdateSkillCoolTimeUI(int32 SlotIndex, float CoolTime);

	void UpgradeSkillLevelUI(int32 SlotIndex, int32 SkillLevelSlotIndex);
	
	FORCEINLINE TArray<UPlayerSkillSlotWidget*> GetPlayerSkillSlotArr() const {return PlayerSkillSlotArray;}
	
};
