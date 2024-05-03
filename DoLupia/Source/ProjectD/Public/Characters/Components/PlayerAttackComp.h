// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "PlayerAttackComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTD_API UPlayerAttackComp : public UActorComponent
{
	GENERATED_BODY()
	
	friend class AProjectDPlayerController;
	
public:	
	// Sets default values for this component's properties
	UPlayerAttackComp();

private:
	class AProjectDCharacter* Player;
	class UPlayerFSMComp* PlayerFSMComp;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	

	// <---------------------- Attack ---------------------->
private:

protected:
	void Attack();
	
public:

	
	
};
