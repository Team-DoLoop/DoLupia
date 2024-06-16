// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AITxtHandlerBase.generated.h"

class UMaterialInstanceDynamic;
class UMaterialInterface;
class UAIConnectionLibrary;
class UTimelineComponent;
class UCurveFloat;
class UTexture2DDynamic;
class USkeletalMeshComponent;
class APlayerGameMode;

UCLASS()
class PROJECTD_API AAITxtHandlerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAITxtHandlerBase();

	// Called every frame
	virtual void Tick( float DeltaTime ) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Update actor's material
	void UpdateActorMaterial();

private:
	UPROPERTY( EditDefaultsOnly )
	class USkeletalMeshComponent* meshComp;

	UPROPERTY( EditDefaultsOnly )
	class UAIConnectionLibrary* AIlib;

	UPROPERTY()
	APlayerGameMode* gm;

	UPROPERTY( EditAnywhere , Category = "Materials" )
	UMaterialInterface* AITxtMaterial;

	void LoadWebImage();

	UFUNCTION()
	void OnImageDownloaded( UTexture2DDynamic* DownloadedTexture );

	UFUNCTION()
	void OnImageDownloadFailed( UTexture2DDynamic* DownloadedTexture );
	

	


	/* ------------- TimeLine ---------------- */
	UFUNCTION()
	void UpdateDissolve( float dissolve );

	UFUNCTION()
	void OnTimelineFinished();

	UMaterialInstanceDynamic* DynamicMaterial;

	// Timeline component
	UPROPERTY()
	class UTimelineComponent* TimelineComp;

	float TimelineLength;

	// Curve for timeline
	UPROPERTY( EditAnywhere , Category = "Timeline" )
	class UCurveFloat* AlphaCurve;

	UTexture2DDynamic* NewTexture;

};
