// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/AITxtHandlerBase.h"
#include "AITxtBossAttack.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API AAITxtBossAttack : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAITxtBossAttack();

	// Called every frame
	virtual void Tick( float DeltaTime ) override;

	// Update actor's material
	void UpdateActorMaterial();

	UFUNCTION()
	void UpdateDissolve( float dissolve );

	UFUNCTION()
	void OnTimelineFinished();

	UPROPERTY( EditAnywhere , Category = "Materials" )
	UMaterialInterface* AITxtMaterial;

	UPROPERTY( EditDefaultsOnly )
	class UStaticMeshComponent* meshComp1;

	UPROPERTY( EditDefaultsOnly )
	class UStaticMeshComponent* meshComp2;

	UPROPERTY( EditDefaultsOnly )
	class UStaticMeshComponent* meshComp3;

	UPROPERTY( EditDefaultsOnly )
	class UStaticMeshComponent* meshComp4;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void LoadWebImage();

	UFUNCTION()
	void OnImageDownloaded( UTexture2DDynamic* DownloadedTexture );

	UFUNCTION()
	void OnImageDownloadFailed( UTexture2DDynamic* DownloadedTexture );


	UPROPERTY( EditDefaultsOnly )
	class UAIConnectionLibrary* AIlib;


	/* ------------- TimeLine ---------------- */
	UMaterialInstanceDynamic* DynamicMaterial1;
	UMaterialInstanceDynamic* DynamicMaterial2;
	UMaterialInstanceDynamic* DynamicMaterial3;
	UMaterialInstanceDynamic* DynamicMaterial4;

	// Timeline component
	UPROPERTY()
	class UTimelineComponent* TimelineComp;

	float TimelineLength;

	// Curve for timeline
	UPROPERTY( EditAnywhere , Category = "Timeline" )
	class UCurveFloat* AlphaCurve;

	UTexture2DDynamic* NewTexture;

	
};
