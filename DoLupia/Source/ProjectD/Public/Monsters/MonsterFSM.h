// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MonsterFSM.generated.h"

UENUM(BlueprintType)
enum class EMonsterState : uint8
{
	Patrol,
	Move,
    Attack,
    Damage,
    Die,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTD_API UMonsterFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMonsterFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMonsterState state;

	void PatrolState();
	void MoveState();
	void AttackState();
	void DamageState();
	void DieState();

	//플레이어를 타겟으로 설정
	UPROPERTY(EditAnywhere)
	AActor* target;

	UPROPERTY(EditAnywhere)
	class AMonster* me;

	FVector TargetVector;

	//일정 반경 안에 들어오면 플레이어를 향해 이동
	UPROPERTY(EditAnywhere)
	float TargetRange = 700;

	//일정 반경 안에 들어오면 공격모드로 전환
	UPROPERTY( EditAnywhere )
	float AttackRange = 500;

	void MoveToTarget();

	void TakeDamage();

	float currentTime=0;
};
