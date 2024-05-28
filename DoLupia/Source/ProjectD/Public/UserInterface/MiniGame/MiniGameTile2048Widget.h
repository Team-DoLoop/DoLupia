// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MiniGameTile2048Widget.generated.h"

class UImage;
class UButton;

UENUM()
enum E2048Color
{
	None,
	Red,
	Orange,
	Yellow,
	Green,
	Blue,
	Indigo,
	Purple,
	ClearColor 
};


UCLASS()
class PROJECTD_API UMiniGameTile2048Widget : public UUserWidget
{
	GENERATED_BODY()

public:

	FORCEINLINE E2048Color GetTileValue() const { return TileValue; }

	void SetTileValue( E2048Color NewColor );
	void SetTileValue( uint32 NewTileValue );

	void ReStartMiniGame();

	void PlayScaleAnimation( float TargetScale );
	void PlayMergeAnimation( float Duration );
	void PlayMoveAnimation( float Duration );

	UFUNCTION()
	void OnScaleAnimationFinished();

	UFUNCTION()
	void OnMoveAnimationFinished();

	UPROPERTY( meta = (BindWidget) )
	class UTextBlock* Test;


protected:
	virtual void NativeConstruct() override; 

protected:
	UPROPERTY( meta = (BindWidget) )
	UImage* TileImage;

	//UPROPERTY( meta = (BindWidget) )
	//UButton* Button;

	UPROPERTY( EditDefaultsOnly )
	UTexture2D* TextureDefault;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* Texture1;
	UPROPERTY( EditDefaultsOnly )
	UTexture2D* Texture2;
	UPROPERTY( EditDefaultsOnly )
	UTexture2D* Texture3;
	UPROPERTY( EditDefaultsOnly )
	UTexture2D* Texture4;
	UPROPERTY( EditDefaultsOnly )
	UTexture2D* Texture5;
	UPROPERTY( EditDefaultsOnly )
	UTexture2D* Texture6;
	UPROPERTY( EditDefaultsOnly )
	UTexture2D* Texture7;
	UPROPERTY( EditDefaultsOnly )
	UTexture2D* Texture8;

	UPROPERTY( BlueprintReadOnly , Category = "BindAnimation" , meta = (BindWidgetAnim) , Transient )
	class UWidgetAnimation* ScaleAnimation; // 애니메이션 변수 선언

	UPROPERTY( BlueprintReadOnly , Category = "BindAnimation" , meta = (BindWidgetAnim) , Transient )
	class UWidgetAnimation* MoveAnimation; // 애니메이션 변수 선언

	UPROPERTY( BlueprintReadOnly , Category = "BindAnimation" , meta = (BindWidgetAnim) , Transient )
	class UWidgetAnimation* MergeAnimation; // 애니메이션 변수 선언
	

private:
	E2048Color TileValue;
	FWidgetAnimationDynamicEvent EndDelegate;
	FWidgetAnimationDynamicEvent MoveEndDelegate;
};
