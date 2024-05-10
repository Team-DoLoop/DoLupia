// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Item/LootingItemWidget.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"


void ULootingItemWidget::SetMyWidget( const FText& ItemName , int32 ItemQuantity , UTexture2D* ItemImage )
{
	Quantity->SetText( FText::FromString( FString::FromInt( ItemQuantity ) ) );
	Name->SetText( ItemName );
	Image->SetBrushFromTexture( ItemImage );
}
