// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "InterfaceTestActor.generated.h"

UCLASS()
class PROJECTD_API AInterfaceTestActor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	AInterfaceTestActor();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Test Actor")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Test Actor")
	FInteractableData InstanceInteractableData;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	virtual void BeginInteract() override;
	virtual void EndInteract() override;
	virtual void Interact(class AProjectDCharacter* PlayerCharacter) override;
};
