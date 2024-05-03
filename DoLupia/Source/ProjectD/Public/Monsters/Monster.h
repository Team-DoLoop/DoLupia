// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"

UCLASS()
class PROJECTD_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
	void OnMyCompBeginOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , 
		UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult );

	UPROPERTY(EditAnywhere)
	class USphereComponent* sphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FSMComponent)
	class UMonsterFSM* MonsterFSM;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	int32 maxHP = 100;

	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	int32 currentHP = maxHP;


	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly )
	class UWidgetComponent* healthUI;

	UPROPERTY()
	class UMonsterHPWidget* monsterHPWidget;

	void OnMyTakeDamage(int damage);
};
