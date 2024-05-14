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

protected:
	virtual void BeginPlay() override;
	UTexture2D* LoadTextureFromImage( const FString& ImagePath );
	UMaterialInterface* CreateMaterialFromTexture( UTexture2D* Texture );
	void ApplyMaterialToMesh( UMeshComponent* MeshComponent , UMaterialInterface* Material );

	UPROPERTY( EditDefaultsOnly )
	class UStaticMeshComponent* meshComp;

	UPROPERTY( EditDefaultsOnly )
	class UBoxComponent* boxComp;

	UPROPERTY( EditAnywhere , Category = "Materials" )
	UMaterialInterface* MaterialTemplate;


};
