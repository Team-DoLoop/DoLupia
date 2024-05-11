// Fill out your copyright notice in the Description page of Project Settings.


#include "Pooling/ItemWidgetPool.h"
#include "UserInterface/Item/LootingItemWidget.h"
#include "Items/ItemBase.h"

UItemWidgetPool::UItemWidgetPool()
{

}

void UItemWidgetPool::AddWidget(TSubclassOf<ULootingItemWidget> WidgetFactory)
{
	constexpr int32 MaxWidget = 7;
	LootingWidgetFactory = WidgetFactory;
	for (int32 i = 0; i < MaxWidget; ++i)
	{
		TObjectPtr<ULootingItemWidget> LootingWidget = CreateWidget<ULootingItemWidget>( GetWorld() , LootingWidgetFactory );
		PoolWidget.Add( LootingWidget );
	}
}

ULootingItemWidget* UItemWidgetPool::GetWidget( FText ItemName, int32 Quantity, UTexture2D* Icon )
{
	TObjectPtr<ULootingItemWidget> LootingWidget = nullptr;
	
	int32 PoolSize = PoolWidget.Num();

	if (PoolSize != 0)
	{
		LootingWidget = PoolWidget[--PoolSize];
		PoolWidget.RemoveAt(PoolSize);
	}
	else
		LootingWidget = CreateWidget<ULootingItemWidget>( GetWorld() , LootingWidgetFactory );
		
	LootingWidget->SetMyWidget( ItemName , Quantity , Icon );
	

	return LootingWidget;
}

void UItemWidgetPool::ReturnWidget( ULootingItemWidget* Widget )
{
	Widget->SetRenderOpacity(1.f);
	Widget->SetVisibility(ESlateVisibility::Hidden);
	PoolWidget.Add(Widget);
}
