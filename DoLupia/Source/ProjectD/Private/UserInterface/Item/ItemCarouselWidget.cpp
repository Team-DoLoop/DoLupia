// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Item/ItemCarouselWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/ScrollBox.h"
#include "Pooling/ItemWidgetPool.h"
#include "Pooling/SoundManager.h"
#include "UserInterface/Item/LootingItemWidget.h"

UItemCarouselWidget::UItemCarouselWidget(const FObjectInitializer& ObjectInitializer)
    : Super( ObjectInitializer )
{
    ItemWidgetPool = CreateDefaultSubobject<UItemWidgetPool>( TEXT( "ItemWidgetPool" ) );
    
}

void UItemCarouselWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry , InDeltaTime);

    // 아이템을 부드럽게 스크롤하기 위해 Tick마다 아이템의 위치를 업데이트
    MoveItemsUp( InDeltaTime );
}

void UItemCarouselWidget::NativeConstruct()
{
    Super::NativeConstruct();
    ItemWidgetPool->AddWidget( LootingWidgetFactory );

    FTimerHandle Handle;
    GetWorld()->GetTimerManager().SetTimer
	( 
		Handle, FTimerDelegate::CreateLambda([&](){ ItemCarouselTrigger = true;}), 0.1f, false
    );
}

void UItemCarouselWidget::AddItemWidget( FText ItemName , int32 Quantity , UTexture2D* Icon )
{
    if(ItemCarouselTrigger)
    {
        ULootingItemWidget* Widget = ItemWidgetPool->GetWidget( ItemName , Quantity , Icon );
        WidgetBox->AddChild( Widget );
    }

    // 사운드 추가
    if(GetItemSFX)
        ASoundManager::GetInstance( GetWorld() )->PlaySoundWave2D( GetItemSFX , EPlayerSound::PlayerSound4 , 0.25f );
}


void UItemCarouselWidget::SlideWidget()
{
    ItemWidgetPool->ReturnWidget(Cast<ULootingItemWidget>(WidgetBox->GetChildAt(0)));
    WidgetBox->RemoveChildAt(0);
}

void UItemCarouselWidget::MoveItemsUp(float DeltaTime)
{
    // 아이템을 부드럽게 스크롤하기 위해 속도를 조절

    bool IsViewWidget = false;
    FVector2D Original( 0 , 300 );  // 이미지 위젯의 위치를 조정하여 자연스럽게 위로 이동

    for (int32 i = 0; i < WidgetBox->GetChildrenCount(); ++i)
    {
	    if (ULootingItemWidget* LootingItemWidget = Cast<ULootingItemWidget>( WidgetBox->GetChildAt( i ) ))
        {
			if(LootingItemWidget->GetVisibility() == ESlateVisibility::Hidden)
                LootingItemWidget->SetVisibility(ESlateVisibility::Visible);

            
            FVector2D Offset( 0.0 , 0.0 ); // 각 아이템을 위로 20픽셀씩 이동
            float& LifeTime = LootingItemWidget->GetLifeTime();

            if (LifeTime >= 1.5f)
				continue;

            IsViewWidget = true;

            LifeTime += DeltaTime;

            // 가속도를 추가하여 점차적으로 속도가 증가하도록 함
            float& WidgetSpeed = LootingItemWidget->GetSmoothScrollSpeed();
            WidgetSpeed += DeltaTime * 100.f;
            Offset.Y -= WidgetSpeed;

            LootingItemWidget->SetRenderOpacity( 1.5f / LifeTime - 1.f );
            LootingItemWidget->SetRenderTranslation( Original + Offset );
        }
    }

    // 최대 아이템 개수를 초과하는 경우 가장 아래에 있는 아이템을 제거
    if(!IsViewWidget)
    {
        
        for(int32 i = WidgetBox->GetChildrenCount() - 1; i >= 0; --i)
        {
            ULootingItemWidget* LootingItemWidget = Cast<ULootingItemWidget>( WidgetBox->GetChildAt( i ));
            WidgetBox->RemoveChild( LootingItemWidget );
            ItemWidgetPool->ReturnWidget( LootingItemWidget );
        }
    }
}
