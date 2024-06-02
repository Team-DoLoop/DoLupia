// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BossDrone.generated.h"

class ABossMonster;
class ABossDroneLaser;
class USkeletalMeshComponent;

UENUM()
enum class LaserOnGroundPattern : uint8
{
	LOGP_Circle,
	LOGP_Square,
	LOGP_Star
};

UCLASS()
class PROJECTD_API ABossDrone : public APawn
{
	GENERATED_BODY()


public:	
	ABossDrone();

	FORCEINLINE void SetBossIntervalLocation(const FVector& NewBossIntervalLocation) { BossIntervalLocation = NewBossIntervalLocation;}
	FORCEINLINE void SetCurrentAngle(float NewCurrentAngle) { CurrentAngle = NewCurrentAngle; }
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


private:
	void LaserOnGround( LaserOnGroundPattern Pattern, FVector Location );

	void FollowBoss( float DeltaTime );
	void Detect() const;
	void Attack();
	void ReturnToBoss();

private:
	enum class EDroneState
	{
		Following,
		AttackSquaring,
		Attacking,
		Returning
	};

	UPROPERTY(EditDefaultsOnly)
	float MovementSpeed = 600.f;

	UPROPERTY( EditDefaultsOnly )
	float AttackRange = 1000.f;

	UPROPERTY( EditDefaultsOnly )
	float OrbitRadius;
	UPROPERTY( EditDefaultsOnly )
	float OrbitSpeed; 
	float CurrentAngle;

	EDroneState CurrentState;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* DroneMeshComponent;


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
