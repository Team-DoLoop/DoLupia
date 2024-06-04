// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/BossMonster.h"
#include "Monsters/MonsterAIController.h"
#include "Engine/World.h"  // 필요
#include "CollisionQueryParams.h"  // 필요
#include "Components/WidgetComponent.h"
#include "Engine/EngineTypes.h"  // 필요
#include "Engine/Engine.h"  // GEngine
#include "Engine/OverlapResult.h"
#include "Kismet/KismetMathLibrary.h"
#include "Monsters/BossAnim.h"
#include "Monsters/MonsterHPWidget.h"
#include "Monsters/AI/BTTask_Attack.h"

// Sets default values
ABossMonster::ABossMonster()
{
	PrimaryActorTick.bCanEverTick = true;


	ConstructorHelpers::FObjectFinder<USkeletalMesh>BossMonsterMesh( TEXT( "/Game/Asset/Character/Sci_Fi_Droid_Mee/Mesh/Character/SK_Mee_Droid_Mesh.SK_Mee_Droid_Mesh" ) );
	if (BossMonsterMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh( BossMonsterMesh.Object );
	}
	
	//OctopusBackpackComponent = CreateDefaultSubobject<UOctopusBackpackComponent>( TEXT( "OctopusBackpackComponent" ) );
	ChildActorComponent = CreateDefaultSubobject<UChildActorComponent>( TEXT( "ChildActorComponent" ) );
	ChildActorComponent->SetChildActorClass( AOctopusBackpackActor::StaticClass() );

	FName OctoSocket( TEXT( "OctoSocket" ) );
	if (GetMesh()->DoesSocketExist( OctoSocket ))
	{
		ChildActorComponent->SetupAttachment( GetMesh(),OctoSocket );
	}

	AIControllerClass = AMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}


// Called when the game starts or when spawned
void ABossMonster::BeginPlay()
{
	Super::BeginPlay();
	IsAlive = true;
	state = EBossState::Idle;
	skillState = EBossSkill::Hit;
	anim = Cast<UBossAnim>( this->GetMesh()->GetAnimInstance() );
	//OctopusBackpackComponent->OctopusBackpackBattleMode( true );
	
	InitializeAttackStack();

	
}

// Called every frame
void ABossMonster::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	//// 보스의 위치와 회전 업데이트
	//FVector NewLocation = GetActorLocation() + FVector( 1.0f , 0.0f , 0.0f );
	//SetActorLocation( NewLocation );

	//// Child Actor의 위치와 회전 업데이트
	//if (ChildActorComponent)
	//{
	//	ChildActorComponent->SetWorldLocation( NewLocation );
	//}

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
	anim->animState = state;
}

void ABossMonster::MoveState()
{
	//UE_LOG( LogTemp , Warning , TEXT( "ABossMonster::MoveState()" ) );
	anim->animState = state;
	anim->bAttackState = false;
}

void ABossMonster::AttackState()
{
	//UE_LOG( LogTemp , Warning , TEXT( "ABossMonster::AttackState()" ) );
	attackDelayTime= UKismetMathLibrary::RandomIntegerInRange( 2,4 );
	anim->bAttackState = true;
	anim->animState = state;

	UE_LOG( LogTemp , Warning , TEXT( "currentTime : %f" ),currentTime );

	auto player = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (player)
	{
		FVector direction = player->GetActorLocation() - this->GetActorLocation();
		direction.Z = 0.0f;
		direction.Normalize();

		if(anim->bIsAttackComplete)
		{
			FRotator newRotation = direction.ToOrientationRotator();
			FRotator currentRotation = this->GetActorRotation();
			currentRotation.Yaw = newRotation.Yaw;
			this->SetActorRotation( currentRotation );

			currentTime += GetWorld()->GetDeltaSeconds();
		}
	}

	if (currentTime > attackDelayTime)
	{
		// 스택이 비어있으면 스택을 초기화
		if (AttackStack.Num() == 0)
		{
			InitializeAttackStack();
		}

		// 스택에서 하나씩 꺼내어 공격 실행
		if (AttackStack.Num() > 0)
		{
			anim->bAttackDelay = true;
			UE_LOG( LogTemp , Warning , TEXT( "ABossMonster::Start Attack!!!!" ) );
			void (ABossMonster:: * Attack)() = AttackStack.Pop();
			(this->*Attack)();
			currentTime = 0;
			anim->bIsAttackComplete = false;
		}
	}
	
}

void ABossMonster::DamageState()
{
}

void ABossMonster::DieState()
{
	IsAlive = false;
}

void ABossMonster::HitAttack()
{
	UE_LOG( LogTemp , Warning , TEXT( "ABossMonster::HitAttack()" ) );
	skillState = EBossSkill::Hit;
	anim->animState = state;
	anim->animBossSkill = skillState;
}

void ABossMonster::FireAttack()
{
	UE_LOG( LogTemp , Warning , TEXT( "ABossMonster::FireAttack()" ) );
	skillState = EBossSkill::Fire;
	anim->animState = state;
	anim->animBossSkill = skillState;

	//OctopusBackpackComponent->AttackHand( , 0 );
}

void ABossMonster::GrabAndThrowAttack()
{
	UE_LOG( LogTemp , Warning , TEXT( "ABossMonster::GrabAndThrowAttack()" ) );
	skillState = EBossSkill::GrabAndThrow;
	anim->animState = state;
	anim->animBossSkill = skillState;
}

void ABossMonster::InitializeAttackStack()
{
	// 공격 함수 포인터 배열 초기화
	AttackFunctions = { &ABossMonster::HitAttack, &ABossMonster::FireAttack, &ABossMonster::GrabAndThrowAttack };

	// 공격 함수들을 랜덤하게 스택에 추가
	while (AttackFunctions.Num() > 0)
	{
		int32 Index = UKismetMathLibrary::RandomIntegerInRange( 0 , AttackFunctions.Num() - 1 );
		AttackStack.Push( AttackFunctions[Index] );
		AttackFunctions.RemoveAt( Index );
	}
}

void ABossMonster::GetHitResult()
{
}



