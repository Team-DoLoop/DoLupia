// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OctopusBackpackComponent.h"
#include "OctopusBackpackActor.h"
#include "AI/BTTask_Attack.h"
#include "Components/ActorComponent.h"
#include "BossMonster.generated.h"

UENUM( BlueprintType )
enum class EBossState : uint8
{
	Idle ,
	Move ,
	Attack ,
	Damage ,
	Die ,
};

UCLASS()
class PROJECTD_API ABossMonster : public ACharacter
{
	GENERATED_BODY()

public:
	ABossMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY( EditAnywhere , BlueprintReadWrite, Category = "Components" )
	UOctopusBackpackComponent* OctopusBackpackComponent;
	
	UPROPERTY( EditAnywhere,BlueprintReadWrite , Category = "Components" )
	UChildActorComponent* ChildActorComponent;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	EBossState state;

	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	int32 BossMaxHP = 100;

	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	int32 BossCurrentHP = BossMaxHP;

	bool IsAlive = true;

	void IdleState();
	void MoveState();
	void AttackState();
	void DamageState();
	void DieState();

	UPROPERTY()
	class UBossAnim* anim;
	
};
