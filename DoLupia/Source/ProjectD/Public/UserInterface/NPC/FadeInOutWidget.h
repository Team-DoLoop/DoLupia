// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FadeInOutWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UFadeInOutWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY( BlueprintReadOnly , Category = "BindAnimation" , meta = (BindWidgetAnim) , Transient )
	class UWidgetAnimation* FadeAnimation; // 애니메이션 변수 선언

public:
	void FadeInOut();
	
};
