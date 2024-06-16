// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerType.h"
#include "GameFramework/Actor.h"
#include "TriggerBaseActor.generated.h"

class UBoxComponent;
class APlayerGameMode;
class UNiagaraComponent;
class AProjectDCharacter;
class USpringArmComponent;
class UTimelineComponent;
class UCurveFloat;

UCLASS()
class PROJECTD_API ATriggerBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerBaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	UBoxComponent* triggerComp;

	UPROPERTY()
	APlayerGameMode* gm;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	EPlayerTriggerType triggerType = EPlayerTriggerType::None;

	/* ------------------- Open Level ------------------- */
public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Change Level" )
	FName LvName;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	UNiagaraComponent* locationVFX;

	void CallLevel( FName Lvname, AProjectDCharacter* Character );
	void ShowTrigger();
	void HideTrigger();

	void ActiveTriggerCollision();

	/* ------------------- CameraBoom ------------------- */
private:
	void ChangeCameraAngle(float angle);
	void ChangeCameraBooms( float angle );

	UPROPERTY()
	USpringArmComponent* CameraBoom;

	// lerp 적용
	UPROPERTY()
	UTimelineComponent* TimelineComp;

	FRotator InitialRotation;
	FRotator TargetRotation;

	UFUNCTION()
	void HandleTimelineProgress( float Value );

	UFUNCTION()
	void OnTimelineFinished();

	UPROPERTY( EditAnywhere , Category = "Timeline" )
	UCurveFloat* CurveFloat;

};
