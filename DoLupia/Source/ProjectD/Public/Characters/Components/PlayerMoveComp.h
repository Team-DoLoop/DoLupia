// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerMoveComp.generated.h"


class UNiagaraSystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTD_API UPlayerMoveComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerMoveComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	
	// <---------------------- Player ---------------------->
private:
	UPROPERTY()
	class AProjectDCharacter* Player;

	UPROPERTY()
	class AProjectDPlayerController* PlayerController;

	UPROPERTY()
	class UPlayerFSMComp* PlayerFSN;
	
protected:

public:
	
	
	
	// <---------------------- Move ---------------------->
private:
	FVector CachedDestination;

	// bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed
	
protected:

public:
	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** Time Threshold to know if it was a short press */
	// Default = 0.3f
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();

	

	// <---------------------- Evasion ---------------------->
private:

protected:
	
public:
	void Evasion();

	
};
