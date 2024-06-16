// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LocationMarker.generated.h"

class UNiagaraComponent;
class UBoxComponent;
class UMeshComponent;
class UMapIconComponent;

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

	void ActiveLocationMarker();

	UFUNCTION( BlueprintCallable , Category = "Marker" )
	int32 GetMarkerID() const { return MarkerID; }

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Marker" )
	int32 MarkerID;

	UPROPERTY( VisibleAnywhere )
	UBoxComponent* BoxComponent; // BoxComponent 포인터 생성

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	UNiagaraComponent* locationVFX;

	UPROPERTY()
	FText LocationName;

	UPROPERTY(EditAnywhere)
	FString ObjectiveID;

	/*---------------------- Minimap ------------------*/
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = Camera , meta = (AllowPrivateAccess = "true") )
	class UMapIconComponent* MapIcon;
};
