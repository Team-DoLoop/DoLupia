// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemWidgetPool.generated.h"

class ULootingItemWidget;
class UItemBase;
class FText;
class UTexture2D;

/**
 * 
 */
UCLASS()
class PROJECTD_API UItemWidgetPool : public UObject
{
	GENERATED_BODY()
	
public:
    UItemWidgetPool();

    void AddWidget( TSubclassOf<ULootingItemWidget> LootingWidgetFactory );

    // 풀에서 위젯 가져오기
    ULootingItemWidget* GetWidget( FText ItemName , int32 Quantity , UTexture2D* Icon );

    // 사용한 위젯을 풀로 반환하기
    void ReturnWidget( ULootingItemWidget* Widget );

private:
    UPROPERTY(VisibleAnywhere)
    TArray<TObjectPtr<ULootingItemWidget>> PoolWidget;

    TSubclassOf<ULootingItemWidget> LootingWidgetFactory;


    
};
