// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerSkillSlotWidget.generated.h"

class AProjectDCharacter;
enum class EUseColor : uint8;
/**
 * 
 */
struct FSkillInfo;
struct FPlayerSkillData;
UCLASS()
class PROJECTD_API UPlayerSkillSlotWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized ( ) override;
	virtual void NativeConstruct ( ) override;
	
private:
	UPROPERTY()
	AProjectDCharacter* Player;
	
	int32 SkillLevel = 1;
	int SlotIndex = 0;
	
	TMap<EUseColor, FLinearColor> ProgressBarColor;
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* SkillThumnail;
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* CoolTimeImage;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UHorizontalBox* SkillLevelBox;

	UPROPERTY()
	TArray<class UImage*> SkillLevelSlot;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* SkillLockImage;

	UPROPERTY()
	UMaterialInstanceDynamic* MaterialInstanceDynamic;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* Icon;

	
public:
	void InitUI();
	void InitSkillLevelUI();

	void SetUI(FPlayerSkillData* _SkillData);
	void SetCoolTimeBar(float CoolTime);

	void UpgradeSkillSlotLevelUI(int32 SkillLevel);
	
	FORCEINLINE void SetSkillIndex(int32 _SlotIndex){SlotIndex = _SlotIndex;}

	void SetSkillLockImage(bool IsSkillLock);



	// <---------------- Combo ---------------->
private:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* CanComboImage;

	UPROPERTY(EditDefaultsOnly,Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* ComboClickAnimation;

public:
	void SetSkillComboSlotUI(bool IsCanCombo);
};
