// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OctopusBackpackComponent.h"
#include "OctopusBackpackActor.h"
#include "SpawnMonsterDamage.h"
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

UENUM( BlueprintType )
enum class EBossSkill : uint8
{
	Hit ,
	Fire ,
	Grab,
	Throw,
	BlastFire ,
	BlastLightening ,
};

UENUM( BlueprintType )
enum class EBossDelay : uint8
{
	LookAround ,
	Launch ,
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
	virtual void Tick( float DeltaTime ) override;

	//UPROPERTY( EditAnywhere , BlueprintReadWrite, Category = "Components" )
	//UOctopusBackpackComponent* OctopusBackpackComponent;

	UPROPERTY( EditAnywhere )
	class USphereComponent* AttackCollision;

	UFUNCTION()
	void OnMyBeginOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult );

	UFUNCTION()
	void OnLaunchBeginOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult );

	//UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Components" )
	//UChildActorComponent* ChildActorComponent;

	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly )
	class UWidgetComponent* healthUI;

	UPROPERTY()
	class UBossHPWidget* BossHPWidget;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	EBossState state;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	EBossSkill skillState;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	EBossDelay delayState;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	int32 BossMaxHP = 6000;

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

	float currentTime = 0;
	float attackDelayTime = 3;

	// ---------ATTACK-------------
	void HitAttack();
	void FireAttack();
	void GrabAttack();
	void ThrowAttack();
	void BlastFire();
	void BlastLightening();

	TArray<void(ABossMonster::*)()> AttackFunctions;
	TArray<void(ABossMonster::*)()> AttackStack;

	void InitializeAttackStack();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bGrab = false;

	bool IsShieldActive = false;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	bool IsPlayerAttackEnabled = true;

	//-----------DELAY-------------
	void LookAround();
	void Launch();

	TArray<void(ABossMonster::*)()> DelayFunctions;
	TArray<void(ABossMonster::*)()> DelayStack;

	void InitializeDelayStack();

	//delay 애니메이션 한번만 호출되도록
	bool IsDelaying = true;
	UPROPERTY( BlueprintReadWrite )
	bool IsLaunching = false;

	//--------------Damage-----------------
	void OnMyTakeDamage( int damage );

	UPROPERTY( EditAnywhere )
	TSubclassOf<ASpawnMonsterDamage> monsterDamageWidget;


	//---------------Die--------------------

	void DestroyMonster();
};
