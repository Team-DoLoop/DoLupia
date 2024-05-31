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

	//friend class ABossDroneLaser;

public:	
	// Sets default values for this actor's properties
	ABossDrone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
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

	EDroneState CurrentState;

	UPROPERTY()
	USkeletalMeshComponent* MeshComponent;

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

	UPROPERTY()
	ABossDroneLaser* LaserActor;
};
