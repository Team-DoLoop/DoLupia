// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIMarterialTestActor.generated.h"

UCLASS()
class PROJECTD_API AAIMarterialTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIMarterialTestActor();
	
	// Called every frame
	virtual void Tick( float DeltaTime ) override;

	// Update actor's material
	void UpdateActorMaterial();

	void LoadWebImage();

	UFUNCTION()
	void OnImageDownloaded( UTexture2DDynamic* DownloadedTexture );

	UFUNCTION()
	void OnImageDownloadFailed( UTexture2DDynamic* DownloadedTexture );

	// Function to update the Alpha value
	UFUNCTION()
	void UpdateAlpha( float Alpha );

	// Function to handle timeline finished
	UFUNCTION()
	void OnTimelineFinished();


protected:
	virtual void BeginPlay() override;
	

	UPROPERTY( EditDefaultsOnly )
	class UStaticMeshComponent* meshComp;

	UPROPERTY( EditDefaultsOnly )
	class UBoxComponent* boxComp;

	// Dynamic Material Instance
	UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY( EditAnywhere , Category = "Materials" )
	UMaterialInterface* MaterialTemplate;

	UPROPERTY( EditAnywhere , Category = "Materials" )
	UMaterialInterface* MaterialTemplate2;

	UPROPERTY( EditDefaultsOnly )
	class UAIConnectionLibrary* AIlib;

	// Timeline component
	UPROPERTY()
	class UTimelineComponent* TimelineComponent;

	// Curve for timeline
	UPROPERTY( EditAnywhere , Category = "Timeline" )
	class UCurveFloat* AlphaCurve;

	// New texture to transition to
	class UTexture2DDynamic* NewTexture;

};
