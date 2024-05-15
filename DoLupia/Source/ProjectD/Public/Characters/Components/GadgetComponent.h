// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GadgetComponent.generated.h"

class AClothes_HeadBase;
class AClothes_TopBase;
class AClothes_PantsBase;
class AClothes_ShoesBase;
class ASwordBase;
class AEquipItemBase;
class UItemBase;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTD_API UGadgetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGadgetComponent();

	UItemBase* ChangeItem( UItemBase* ItemBase ) const;
	void InitEquip();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	UPROPERTY(VisibleAnywhere, Category = "Equipment")
	AClothes_HeadBase* HeadBase;
	UPROPERTY( VisibleAnywhere, Category = "Equipment" )
	AClothes_TopBase* TopBase;
	UPROPERTY( VisibleAnywhere, Category = "Equipment" )
	AClothes_PantsBase* PantsBase;
	UPROPERTY( VisibleAnywhere, Category = "Equipment" )
	AClothes_ShoesBase* ShoesBase;
	UPROPERTY( VisibleAnywhere, Category = "Equipment" )
	ASwordBase* SwordBase;

public:
	FORCEINLINE class ASwordBase* GetSword() const { return SwordBase; }

};
