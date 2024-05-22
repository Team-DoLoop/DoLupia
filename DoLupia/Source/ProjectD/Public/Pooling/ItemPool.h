// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemPool.generated.h"

class UItemBase;

/**
 * 
 */
UCLASS()
class PROJECTD_API UItemPool : public UObject
{
	GENERATED_BODY()

public:
    UItemPool();

    // 미리 생성해서 가져오기
    void CreateItem(int32 NumberOfCreate);

    // 풀에서 아이템 가져오기
    UItemBase* GetItem(const FString& ItemID);

    // 사용한 아이템을 풀로 반환하기
    void ReturnItem( UItemBase* Item );
	
private:
    UPROPERTY(VisibleAnywhere)
    TArray<TObjectPtr<UItemBase>> Pool;

    UPROPERTY( VisibleAnywhere )
    TMap<FString, TObjectPtr<UItemBase>> ItemManager;


    UPROPERTY(EditDefaultsOnly, Category = "Item Initialization" )
    UDataTable* ItemDataTable;
};
