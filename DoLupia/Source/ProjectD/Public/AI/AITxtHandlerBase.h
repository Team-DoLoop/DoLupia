// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AITxtHandlerBase.generated.h"

UCLASS()
class PROJECTD_API AAITxtHandlerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAITxtHandlerBase();

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
	class USkeletalMeshComponent* meshComp;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void LoadWebImage();

	UFUNCTION()
	void OnImageDownloaded( UTexture2DDynamic* DownloadedTexture );

	UFUNCTION()
	void OnImageDownloadFailed( UTexture2DDynamic* DownloadedTexture );
	

	UPROPERTY( EditDefaultsOnly )
	class UAIConnectionLibrary* AIlib;


	/* ------------- TimeLine ---------------- */
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
