// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/BossMonster.h"
#include "Monsters/MonsterAIController.h"
#include "Engine/World.h"  // 필요
#include "CollisionQueryParams.h"  // 필요
#include "Engine/EngineTypes.h"  // 필요
#include "Engine/Engine.h"  // GEngine
#include "Engine/OverlapResult.h"
#include "Monsters/AI/BTTask_Attack.h"

// Sets default values
ABossMonster::ABossMonster()
{
	PrimaryActorTick.bCanEverTick = true;


	ConstructorHelpers::FObjectFinder<USkeletalMesh>BossMonsterMesh( TEXT( "/Game/Asset/Character/Sci_Fi_Droid_Mee/Mesh/Character/SK_Mee_Droid_Mesh.SK_Mee_Droid_Mesh" ) );
	if (BossMonsterMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh( BossMonsterMesh.Object );
	}
	/*
	OctopusBackpackComponent = CreateDefaultSubobject<UOctopusBackpackComponent>( TEXT( "OctopusBackpackComponent" ) );
	ChildActorComponent = CreateDefaultSubobject<UChildActorComponent>( TEXT( "ChildActorComponent" ) );

	FName OctoSocket( TEXT( "OctoSocket" ) );
	if (GetMesh()->DoesSocketExist( OctoSocket ))
	{
		ChildActorComponent->SetupAttachment( GetMesh(),OctoSocket );

	}
	*/
	//ChildActorComponent->SetupAttachment( GetMesh());



	AIControllerClass = AMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}


// Called when the game starts or when spawned
void ABossMonster::BeginPlay()
{
	Super::BeginPlay();
	IsAlive = true;
	state = EBossState::Idle;
}

// Called every frame
void ABossMonster::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	switch (state)
	{
	case EBossState::Idle:		IdleState();		break;
	case EBossState::Move:		MoveState();		break;
	case EBossState::Attack:	AttackState();		break;
	case EBossState::Damage:	DamageState();		break;
	case EBossState::Die:		DieState();			break;
	}
}

void ABossMonster::IdleState()
{
	//UE_LOG( LogTemp , Warning , TEXT( "ABossMonster::IdleState()" ) );

}

void ABossMonster::MoveState()
{
	//UE_LOG( LogTemp , Warning , TEXT( "ABossMonster::MoveState()" ) );
}

void ABossMonster::AttackState()
{
	//UE_LOG( LogTemp , Warning , TEXT( "ABossMonster::AttackState()" ) );
}

void ABossMonster::DamageState()
{
}

void ABossMonster::DieState()
{
	IsAlive = false;
}



