// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BossDrone.generated.h"

DECLARE_DELEGATE( FTestDelegate );

class ABossMonster;
class ABossDroneLaser;
class USkeletalMeshComponent;
class UAnimMontage;

UENUM( BlueprintType )
enum class EDroneState : uint8
{
	Following ,
	AttackSquaring,
	Attacking,
	Pattern,
	Returning
};

UENUM()
enum class LaserOnGroundPattern : uint8
{
	LOGP_Circle,
	LOGP_Square,
	LOGP_Star
};


UCLASS()
class PROJECTD_API ABossDrone : public ACharacter
{
	GENERATED_BODY()


public:	
	ABossDrone();

	FORCEINLINE void SetBossIntervalLocation(const FVector& NewBossIntervalLocation) { BossIntervalLocation = NewBossIntervalLocation;}
	FORCEINLINE void SetCurrentAngle(float NewCurrentAngle) { CurrentAngle = NewCurrentAngle; }

	FORCEINLINE float GetAttackRange() const { return AttackRange; }
	FORCEINLINE float GetFollowRange() const { return FollowRange; }

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void Attack();

private:
	void LaserOnGround( LaserOnGroundPattern Pattern, FVector Location );

	void FollowBoss( float DeltaTime );
	void Detect() const;
	void ReturnToBoss();

private:
	UPROPERTY(EditDefaultsOnly)
	float MovementSpeed = 600.f;

	UPROPERTY( EditDefaultsOnly )
	float AttackRange = 1000.f;

	UPROPERTY( EditDefaultsOnly )
	float FollowRange = 300.f;

	UPROPERTY( EditDefaultsOnly )
	float OrbitRadius;
	UPROPERTY( EditDefaultsOnly )
	float OrbitSpeed; 
	float CurrentAngle;

	UPROPERTY(EditDefaultsOnly)
	EDroneState CurrentState;


	
	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* DroneMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* DroneAttackMontage;


	FVector BossIntervalLocation;
	FVector AttackTargetLocation;

	TArray<FVector> LaserVectors;

	UPROPERTY(EditDefaultsOnly)
	FVector MuzzleOffSet;

	UPROPERTY( VisibleAnywhere )
	FVector MuzzleStartLocation;
	UPROPERTY( VisibleAnywhere )
	FVector MuzzleEndLocation;

	//플레이어를 타겟으로 설정
	UPROPERTY()
	AActor* Target;

	UPROPERTY()
	ABossMonster* Boss;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABossDroneLaser> LaserFactory;

	UPROPERTY()
	ABossDroneLaser* LaserActor;
};
