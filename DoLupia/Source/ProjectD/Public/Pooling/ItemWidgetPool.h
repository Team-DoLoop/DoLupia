// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemWidgetPool.generated.h"

class ULootingItemWidget;
class UItemBase;

/**
 * 
 */
UCLASS()
class PROJECTD_API UItemWidgetPool : public UObject
{
	GENERATED_BODY()
	
public:
    UItemWidgetPool();

    // 풀에서 위젯 가져오기
    ULootingItemWidget* GetWidget( UItemBase* ItemBase );

    // 사용한 위젯을 풀로 반환하기
    void ReturnWidget( ULootingItemWidget* Widget );

private:
    UPROPERTY(VisibleAnywhere)
    TArray<TObjectPtr<ULootingItemWidget>> PoolWidget;
    
    
};
