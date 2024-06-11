// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerTutorialComp.generated.h"

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



	// <----------------------------- Tutorial UI ----------------------------->
public:
	void SetTutorialUI(FTutorialData* _TutoData);

	
	
	// <----------------------------- Quest ----------------------------->
public:
	void CreateItem(int32 _ItemNum, int32 _Quantity);
	
	UPROPERTY( EditInstanceOnly)
	UDataTable* ItemDataTable;

	
private:
	TMap<int32, FName> ItemIdData;
};
