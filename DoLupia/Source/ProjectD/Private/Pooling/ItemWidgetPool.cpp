// Fill out your copyright notice in the Description page of Project Settings.


#include "Pooling/ItemWidgetPool.h"
#include "UserInterface/Item/LootingItemWidget.h"
#include "Items/ItemBase.h"

UItemWidgetPool::UItemWidgetPool()
{
	constexpr int32 MaxWidget = 6;

	for (int32 i = 0; i < MaxWidget; ++i)
	{
		TObjectPtr<ULootingItemWidget> LootingWidget = CreateWidget<ULootingItemWidget>( GetWorld(), ULootingItemWidget::StaticClass());
		PoolWidget.Add(LootingWidget);
	}
}

ULootingItemWidget* UItemWidgetPool::GetWidget( UItemBase* ItemBase )
{
	TObjectPtr<ULootingItemWidget> LootingWidget = nullptr;
	
	int32 PoolSize = PoolWidget.Num();

	if (PoolSize != 0)
	{
		LootingWidget = PoolWidget[--PoolSize];
		PoolWidget.RemoveAt(PoolSize);
	}
	else
		LootingWidget = CreateWidget<ULootingItemWidget>( GetWorld() , ULootingItemWidget::StaticClass() );
		
	LootingWidget->SetMyWidget( ItemBase->GetTextData().Name, ItemBase->GetQuantity(), ItemBase->GetAssetData().Icon);

	return LootingWidget;
}

void UItemWidgetPool::ReturnWidget( ULootingItemWidget* Widget )
{
	PoolWidget.Add(Widget);
}
