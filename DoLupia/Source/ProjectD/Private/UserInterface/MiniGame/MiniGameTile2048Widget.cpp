// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/MiniGame/MiniGameTile2048Widget.h"

#include "Components/Button.h"
#include "Components/Image.h"

void UMiniGameTile2048Widget::SetTileValue( E2048Color NewColor )
{
	TileValue = NewColor;

	switch (NewColor)
	{
	case None:
		TileImage->SetBrushFromTexture( TextureDefault );
		//TileImage->SetColorAndOpacity( FLinearColor::White );
		break;
	case Red: 
		TileImage->SetColorAndOpacity(FLinearColor::Red);
		break;
	case Orange: 
		TileImage->SetColorAndOpacity( FLinearColor(255.f, 165.f, 0.f) );
		break;
	case Yellow:
		TileImage->SetColorAndOpacity(FLinearColor::Yellow);
		break;
	case Green:
		TileImage->SetColorAndOpacity(FLinearColor::Green);
		break;
	case Blue:
		TileImage->SetColorAndOpacity(FLinearColor::Blue);
		break;
	case Indigo:
		TileImage->SetColorAndOpacity(FLinearColor(75.f, 0.f, 130.f));
		break;
	case Purple:
		TileImage->SetColorAndOpacity(FLinearColor(238.f,130.f,238.f));
		break;
	case ClearColor:
		break;
		default: ;
	}

}

void UMiniGameTile2048Widget::SetTileValue(uint32 NewTileValue)
{

	int32 ColorIndex = 0;
	
	while(NewTileValue > 1)
	{
		NewTileValue = NewTileValue >> 1;
		++ColorIndex;
	}

	TileValue = static_cast<E2048Color>(ColorIndex);


	switch (TileValue)
	{
	case None:
		TileImage->SetBrushFromTexture( TextureDefault );
		//TileImage->SetColorAndOpacity( FLinearColor::White );
		break;
	case Red:
		TileImage->SetBrushFromTexture( Texture1 );
		//TileImage->SetColorAndOpacity( FLinearColor::Red );
		break;
	case Orange:
		TileImage->SetBrushFromTexture( Texture2 );
		//TileImage->SetColorAndOpacity( FLinearColor( 255.f , 165.f , 0.f ) );
		break;
	case Yellow:
		TileImage->SetBrushFromTexture( Texture3 );
		//TileImage->SetColorAndOpacity( FLinearColor::Yellow );
		break;
	case Green:
		TileImage->SetBrushFromTexture( Texture4 );
		//TileImage->SetColorAndOpacity( FLinearColor::Green );
		break;
	case Blue:
		TileImage->SetBrushFromTexture( Texture5 );
		//TileImage->SetColorAndOpacity( FLinearColor::Blue );
		break;
	case Indigo:
		TileImage->SetBrushFromTexture( Texture6 );
		//TileImage->SetColorAndOpacity( FLinearColor( 75.f , 0.f , 130.f ) );
		break;
	case Purple:
		TileImage->SetBrushFromTexture( Texture7 );
		//TileImage->SetColorAndOpacity( FLinearColor( 238.f , 130.f , 238.f ) );
		break;
	case ClearColor:
		TileImage->SetBrushFromTexture( Texture8 );
		break;
	default:;
	}
}

void UMiniGameTile2048Widget::ReStartMiniGame()
{
	TileValue = E2048Color::None;
	TileImage->SetBrushFromTexture( TextureDefault );
}

void UMiniGameTile2048Widget::NativeConstruct()
{
	Super::NativeConstruct();

	//Button->OnClicked.AddDynamic(this, &UMiniGameTile2048Widget::ReStartMiniGame );
}
