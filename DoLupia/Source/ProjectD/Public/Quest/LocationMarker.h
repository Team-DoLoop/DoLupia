// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LocationMarker.generated.h"

class UNiagaraComponent;
class UBoxComponent;
class UMeshComponent;

UCLASS()
class PROJECTD_API ALocationMarker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALocationMarker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap( AActor* OtherActor ) override;

	UPROPERTY( VisibleAnywhere )
	UBoxComponent* BoxComponent; // BoxComponent 포인터 생성

	UPROPERTY()
	FText LocationName;

	UPROPERTY(EditAnywhere)
	FString ObjectiveID;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	UNiagaraComponent* locationVFX;

};
