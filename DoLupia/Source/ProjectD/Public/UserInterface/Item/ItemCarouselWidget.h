// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemCarouselWidget.generated.h"

class UItemWidgetPool;
class UItemBase;
class FText;
class UTexture2D;
class ULootingItemWidget;

/**
 * 
 */
UCLASS()
class PROJECTD_API UItemCarouselWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UItemCarouselWidget(const FObjectInitializer& ObjectInitializer);

    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    // 이미지 위젯을 생성하는 함수
    UFUNCTION(Category = "Carousel" )
    void AddItemWidget( FText ItemName, int32 Quantity, UTexture2D* Icon );

protected:
    // 위젯이 생성될 때 호출되는 함수
    virtual void NativeConstruct() override;

private:
    // 위젯을 슬라이드하는 함수
    void SlideWidget();

    // 슬라이드 애니메이션 완료 후 호출되는 콜백 함수
    void MoveItemsUp(float DeltaTime);

private:
    // 이미지 위젯을 담을 상위 위젯
    UPROPERTY( meta = (BindWidget) )
    class UScrollBox* WidgetBox;

    // 위젯의 유지 시간 (초)
    UPROPERTY( EditAnywhere , Category = "Widget" )
    float WidgetDuration = 1.5f;

    // 아이템의 부드러운 스크롤 속도
    UPROPERTY( EditAnywhere , Category = "Widget" )
    float SmoothScrollSpeed = 10.0f; 

    // 슬라이딩 애니메이션을 진행할 타이머 핸들
    FTimerHandle SlideTimerHandle;

    UPROPERTY(VisibleAnywhere, Category = "Pool" )
    TObjectPtr<UItemWidgetPool> ItemWidgetPool;

    UPROPERTY(EditDefaultsOnly, Category = "Pool" )
    TSubclassOf<ULootingItemWidget> LootingWidgetFactory;


    const int32 MaxItemCount = 5;

    bool ItemCarouselTrigger = false;
};
