// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerTutorialComp.generated.h"

class UProjectDGameInstance;
class UPlayerDefaultsWidget;
enum class ETutoItemType : uint8;
class AProjectDCharacter;
struct FTutorialData;
enum class EExplainType : uint8;
class UItemBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTD_API UPlayerTutorialComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerTutorialComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	// <----------------------------- Player ----------------------------->
public:

protected:

private:
	UPROPERTY()
	AProjectDCharacter* Player;

	UPROPERTY()
	UProjectDGameInstance* GI;

	

	// <----------------------------- Tutorial Data ----------------------------->
public:
	FORCEINLINE void SetTutorialID(int32 _TutorialID) {TutorialID = _TutorialID;}
	
private:
	FTutorialData* TutoData;
	bool IsFirstIndex;
	int32 TutorialID;
	
	
	// <----------------------------- Tutorial UI ----------------------------->
public:
	void SetTutorialUI(FTutorialData* _TutoData);
	void NextTutorial();
	void EndTutorial(FTutorialData* _TutoData);

	FORCEINLINE void SetDefaultUI(UPlayerDefaultsWidget* _DefaultUI){DefaultUI = _DefaultUI;}

private:
	FString NextString = TEXT("다음");
	FString CloseString = TEXT("닫기");
	
	UPROPERTY()
	UPlayerDefaultsWidget* DefaultUI;




	// <----------------------------- Quest ----------------------------->
public:
	void StartQuest(int32 _QuestID);
	
	
	
	// <----------------------------- Item ----------------------------->
public:
	void CreateItem(ETutoItemType _TutoItemType, int32 _Quantity);
	
	UPROPERTY( EditInstanceOnly)
	UDataTable* ItemDataTable;

	
private:
	TMap<ETutoItemType, FName> ItemIdData;
};
