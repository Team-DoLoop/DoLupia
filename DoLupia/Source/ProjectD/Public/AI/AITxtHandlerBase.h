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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Update actor's material
	void UpdateActorMaterial();
	

private:

	void LoadWebImage();

	UFUNCTION()
	void OnImageDownloaded( UTexture2DDynamic* DownloadedTexture );

	UFUNCTION()
	void OnImageDownloadFailed( UTexture2DDynamic* DownloadedTexture );

	UPROPERTY( EditDefaultsOnly )
	class USkeletalMeshComponent* meshComp;

	UPROPERTY( EditAnywhere , Category = "Materials" )
	UMaterialInterface* AITxtMaterial;

	UPROPERTY( EditDefaultsOnly )
	class UAIConnectionLibrary* AIlib;

};
