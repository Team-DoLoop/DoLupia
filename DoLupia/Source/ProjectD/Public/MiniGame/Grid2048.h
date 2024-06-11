// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid2048.generated.h"

class UMiniGameTile2048Widget;

UCLASS()
class PROJECTD_API AGrid2048 : public AActor
{
	GENERATED_BODY()
	
public:
    AGrid2048();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick( float DeltaTime ) override;

    TArray<TArray<int32>> PreGrid;
    TArray<TArray<int32>> Grid;

    UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "UI" )
    TSubclassOf<UMiniGameTile2048Widget> GridWidgetClass;

    UPROPERTY()
	TArray<UMiniGameTile2048Widget*> GridWidget;

    UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "UI" )
    TSubclassOf<UUserWidget> Explain2048;

    UPROPERTY()
    class UUserWidget* ExplainWidget;

    UFUNCTION( BlueprintCallable , Category = "Grid" )
    void NewGrid();

    UFUNCTION( BlueprintCallable , Category = "Grid" )
    void NewNumber();

    UFUNCTION( BlueprintCallable , Category = "Grid" )
    bool IsFull() const;

    UFUNCTION( BlueprintCallable , Category = "Grid" )
    void Draw();

    UFUNCTION( BlueprintCallable , Category = "Grid" )
    void SquashColumn( TArray<int32>& Column );

    UFUNCTION( BlueprintCallable , Category = "Grid" )
    void FlipVertically();

    UFUNCTION( BlueprintCallable , Category = "Grid" )
    void FlipDiagonally();

    UFUNCTION( BlueprintCallable , Category = "Grid" )
    void Squash( int32 Key );

    void UpdateCell(int32 x, int32 y, int32 Value);

    void ClearGridWidgets();

private:
    bool isSucess = false;

};
