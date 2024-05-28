// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/MiniGame/MiniGameTile2048Widget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Animation/WidgetAnimation.h"
#include "Animation/UMGSequencePlayer.h"
#include "MovieScene.h"
#include <Animation/MovieScene2DTransformTrack.h>
#include <Animation/MovieScene2DTransformSection.h>
#include <MovieSceneSequencePlaybackSettings.h>
#include <Components/CanvasPanelSlot.h>

void UMiniGameTile2048Widget::NativeConstruct()
{
	Super::NativeConstruct();

	EndDelegate.BindDynamic( this , &UMiniGameTile2048Widget::OnScaleAnimationFinished );
	BindToAnimationFinished( ScaleAnimation , EndDelegate );

	MoveEndDelegate.BindDynamic( this , &UMiniGameTile2048Widget::OnMoveAnimationFinished );
	BindToAnimationFinished( MoveAnimation , MoveEndDelegate );
}


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

void UMiniGameTile2048Widget::OnScaleAnimationFinished()
{
	UE_LOG(LogTemp, Warning, TEXT("OnScaleAnimationFinished"));
}

void UMiniGameTile2048Widget::PlayMergeAnimation( float Duration )
{
	if (MergeAnimation)
	{
		PlayAnimation( MergeAnimation , 0.0f , 1 , EUMGSequencePlayMode::Forward , Duration );
	}
}

void UMiniGameTile2048Widget::PlayMoveAnimation( float Duration )
{
	if (MoveAnimation)
	{
		PlayAnimation( MoveAnimation , 0.0f , 1 , EUMGSequencePlayMode::Forward , Duration );
	}
}

void UMiniGameTile2048Widget::OnMoveAnimationFinished()
{
	SetTileValue(TileValue);
}


void UMiniGameTile2048Widget::PlayScaleAnimation( float TargetScale )
{
	if (ScaleAnimation) // MyScaleAnimation은 애니메이션 블루프린트에서 설정한 애니메이션 변수입니다.
	{
		// 애니메이션을 재생하고 애니메이션의 종료를 감지하는 이벤트 핸들러를 등록합니다.
		PlayAnimation( ScaleAnimation , 0.0f , 1 , EUMGSequencePlayMode::Forward , 1.0f );

		// 애니메이션을 시작하기 전에 크기를 설정합니다.
		FVector2D TargetSize( TargetScale , TargetScale );
		SetDesiredSizeInViewport( TargetSize );
	}
}
