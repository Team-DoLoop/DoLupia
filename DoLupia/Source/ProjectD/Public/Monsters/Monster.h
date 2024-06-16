// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterDamageWidget.h"
#include "SpawnMonsterDamage.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"

struct FItemSpawnerInfo;

UENUM( BlueprintType )
enum class EMonsterType : uint8
{
	Strike UMETA(DisplayName = "Strike"),
	Ranged UMETA(DisplayName = "Ranged") ,
};


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

	UPROPERTY(EditAnywhere)
	EMonsterType MonsterType;

	UFUNCTION()
	virtual void OnMyCompBeginOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , 
	                                   UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult );

	UPROPERTY(EditAnywhere)
	class USphereComponent* sphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FSMComponent)
	class UMonsterFSM* MonsterFSM;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	int32 maxHP = 100;

	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	int32 currentHP = maxHP;

	UPROPERTY( EditAnywhere )
	TSubclassOf<ASpawnMonsterDamage> monsterDamageWidget;

	//플레이어를 타겟으로 설정
	UPROPERTY( EditAnywhere )
	AActor* target;

	FVector TargetVector;

	UPROPERTY()
	class UMonsterAnim* anim;

	//State 함수
	virtual void IdleState();
	virtual void MoveState();
	virtual void AttackState();
	virtual void DamageState();
	virtual void DieState();

	bool IsAlive = true;

	bool bHasTarget = false;

	bool bIsAttackComplete = false;

	//일정 반경 안에 들어오면 플레이어를 향해 이동
	UPROPERTY( EditAnywhere )
	float TargetRange = 1500;

	//일정 반경 안에 들어오면 공격모드로 전환
	UPROPERTY( EditAnywhere )
	float AttackRange = 200;

	void MoveToTarget();

	virtual void OnMyTakeDamage(int32 damage) ;

	void DestroyMonster();

	UPROPERTY( EditAnywhere )
	float attackDelayTime = 3;

	float currentTime = 0;

	float patrolTime = 3;

	class AAIController* ai;

	FVector randomPos;

	bool GetRandomPositionInNavMesh( FVector centerLocation , float radius , FVector& dest );

protected:
	// 아이템 스포너
	UPROPERTY(EditAnywhere)
	class AItemSpawner* ItemSpawner;

	UPROPERTY(EditDefaultsOnly)
	TArray<FItemSpawnerInfo> ItemTuples;

	UPROPERTY( EditDefaultsOnly )
	float DissolveSpeed = 30.f;

private:
	UPROPERTY( EditAnywhere , Category = "Effects" )
	UMaterialInstanceDynamic* DynamicDissolveMaterial;

	float Amount = 40.f;

	
	

};
