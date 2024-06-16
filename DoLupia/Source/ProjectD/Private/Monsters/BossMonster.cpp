// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/BossMonster.h"
#include "Monsters/MonsterAIController.h"
#include "Engine/World.h"  // 필요
#include "CollisionQueryParams.h"  // 필요
#include "Characters/ProjectDCharacter.h"
#include "Components/WidgetComponent.h"
#include "Engine/EngineTypes.h"  // 필요
#include "Engine/Engine.h"  // GEngine
#include "Engine/OverlapResult.h"
#include "Kismet/KismetMathLibrary.h"
#include "Monsters/BossAnim.h"
#include "Monsters/BossHPWidget.h"
#include "Monsters/MonsterDamageWidget.h"
#include "Monsters/MonsterHPWidget.h"
#include "Monsters/SpawnMonsterDamage.h"
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
	/*ChildActorComponent = CreateDefaultSubobject<UChildActorComponent>( TEXT( "ChildActorComponent" ) );
	ChildActorComponent->SetChildActorClass( AOctopusBackpackActor::StaticClass() );*/

	/*FName OctoSocket( TEXT( "OctoSocket" ) );
	if (GetMesh()->DoesSocketExist( OctoSocket ))
	{
		ChildActorComponent->SetupAttachment( GetMesh() , OctoSocket );
	}*/

	AIControllerClass = AMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;


	/*healthUI = CreateDefaultSubobject<UWidgetComponent>( TEXT( "healthUI" ) );
	healthUI->SetupAttachment( RootComponent );
	healthUI->SetCastShadow( false );*/

	AttackCollision = CreateDefaultSubobject<USphereComponent>( TEXT( "AttackCollision" ) );
	AttackCollision->SetGenerateOverlapEvents( true );
	AttackCollision->SetupAttachment( GetMesh() );
}


// Called when the game starts or when spawned
void ABossMonster::BeginPlay()
{
	Super::BeginPlay();
	IsAlive = true;
	state = EBossState::Idle;
	skillState = EBossSkill::Hit;
	delayState = EBossDelay::LookAround;
	anim = Cast<UBossAnim>( this->GetMesh()->GetAnimInstance() );

	BossHPWidget = Cast<UBossHPWidget>( healthUI->GetWidget() );
	if (UWorld* World = GetWorld())
	{
		if (BossHPWidget)
		{
			BossHPWidget->AddToViewport();
		}
	}


	//OctopusBackpackComponent->OctopusBackpackBattleMode( true );

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic( this , &ABossMonster::OnMyBeginOverlap );
	AttackCollision->OnComponentBeginOverlap.AddDynamic( this , &ABossMonster::OnLaunchBeginOverlap );

	InitializeAttackStack();



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

void ABossMonster::OnMyBeginOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor ,
	UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
{
	if (AProjectDCharacter* OverlapPlayer = Cast<AProjectDCharacter>( OtherActor )) {

		if (OverlapPlayer->GetController())
		{
			OverlapPlayer->TakeHit( EAttackType::BASIC , EEffectAttackType::NONE , 10 );
		}
	}
}

void ABossMonster::OnLaunchBeginOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor ,
										UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
{
	if (IsLaunching)
	{
		if (AProjectDCharacter* OverlapPlayer = Cast<AProjectDCharacter>( OtherActor )) {

			if (OverlapPlayer->GetController())
			{
				OverlapPlayer->TakeHit( EAttackType::BASIC , EEffectAttackType::NONE , 10 );

			}
		}

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
	attackDelayTime = UKismetMathLibrary::RandomIntegerInRange( 2 , 4 );
	anim->bAttackState = true;
	anim->animState = state;

	auto player = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (player)
	{
		FVector direction = player->GetActorLocation() - this->GetActorLocation();
		direction.Z = 0.0f;
		direction.Normalize();

		if (anim->bIsAttackComplete)
		{
			if (IsAlive)
			{
				FRotator newRotation = direction.ToOrientationRotator();
				FRotator currentRotation = this->GetActorRotation();
				currentRotation.Yaw = newRotation.Yaw;
				this->SetActorRotation( currentRotation );
			}

		}
		if (IsDelaying) // Delay 한번만 호출 되도록
		{

			if (DelayStack.Num() == 0)
			{
				InitializeDelayStack();
			}

			// 스택에서 하나씩 꺼내어 delay 실행
			if (DelayStack.Num() > 0)
			{
				void (ABossMonster:: * Delay)() = DelayStack.Pop();
				(this->*Delay)();
				IsDelaying = false;
				anim->bFinishDelay = false;
			}


		}
		if (anim->bFinishDelay)
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
				anim->bFinishDelay = false;
			}

		}

	}


}

void ABossMonster::DamageState()
{
}

void ABossMonster::DieState()
{
	IsAlive = false;
	anim->animState = state;

}

//=============================ATTACK=============================

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
}

void ABossMonster::GrabAttack()
{
	UE_LOG( LogTemp , Warning , TEXT( "ABossMonster::GrabAttack()" ) );
	skillState = EBossSkill::Grab;
	anim->animState = state;
	anim->animBossSkill = skillState;
	
}

void ABossMonster::ThrowAttack()
{
	UE_LOG( LogTemp , Warning , TEXT( "ABossMonster::ThrowAttack()" ) );
	skillState = EBossSkill::Throw;
	anim->animState = state;
	anim->animBossSkill = skillState;
}

void ABossMonster::BlastFire()
{
	skillState = EBossSkill::BlastFire;
	anim->animState = state;
	anim->animBossSkill = skillState;
}

void ABossMonster::BlastLightening()
{
	skillState = EBossSkill::BlastLightening;
	anim->animState = state;
	anim->animBossSkill = skillState;
}

void ABossMonster::InitializeAttackStack()
{
	// 공격 함수 포인터 배열 초기화
	/*AttackFunctions = { &ABossMonster::HitAttack, &ABossMonster::FireAttack, &ABossMonster::GrabAttack,
						&ABossMonster::BlastFire,&ABossMonster::BlastLightening
						};*/
	AttackFunctions = { &ABossMonster::GrabAttack };
						

	// 공격 함수들을 랜덤하게 스택에 추가
	while (AttackFunctions.Num() > 0)
	{
		int32 Index = UKismetMathLibrary::RandomIntegerInRange( 0 , AttackFunctions.Num() - 1 );
		AttackStack.Push( AttackFunctions[Index] );
		AttackFunctions.RemoveAt( Index );
	}
}
//=============================DELAY=============================
void ABossMonster::LookAround()
{
	UE_LOG( LogTemp , Warning , TEXT( "ABossMonster::Delay - LookAround()" ) );

	delayState = EBossDelay::LookAround;
	anim->animState = state;
	anim->animBossDelay = delayState;
}

void ABossMonster::Launch()
{
	UE_LOG( LogTemp , Warning , TEXT( "ABossMonster::Delay - Launch()" ) );

	delayState = EBossDelay::Launch;
	anim->animState = state;
	anim->animBossDelay = delayState;
	IsLaunching = true;

	//카메라 쉐이킹 추가
}

void ABossMonster::InitializeDelayStack()
{
	DelayFunctions = { &ABossMonster::LookAround, &ABossMonster::Launch };

	while (DelayFunctions.Num() > 0)
	{
		int32 Index = UKismetMathLibrary::RandomIntegerInRange( 0 , DelayFunctions.Num() - 1 );
		DelayStack.Push( DelayFunctions[Index] );
		DelayFunctions.RemoveAt( Index );
	}
}

void ABossMonster::TakeDamage( int damage )
{
	BossCurrentHP -= damage;

	if (BossHPWidget)
	{
		BossHPWidget->SetHP( BossCurrentHP , BossMaxHP );

	}
	//Damage UI 생성
	UWorld* world = GetWorld();
	if (world)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		FRotator rotator;
		FVector  SpawnLocation = GetActorLocation();

		ASpawnMonsterDamage* SpawnedActor = world->SpawnActor<ASpawnMonsterDamage>( monsterDamageWidget , SpawnLocation , rotator , SpawnParams );;
		if (SpawnedActor)
		{
			UMonsterDamageWidget* DamageWidget = Cast<UMonsterDamageWidget>( SpawnedActor->monsterDamageWidget );
			if (DamageWidget)
			{
				DamageWidget->SetDamage( damage );
			}
		}

	}

	if (BossCurrentHP < 0)
	{
		BossCurrentHP = 0;
	}


	if (BossCurrentHP == 0)
	{
		state = EBossState::Die;
	}

	//monsterHPWidget->SetHP( currentHP , maxHP );




}

void ABossMonster::DestroyMonster()
{
	//플레이어 델리게이트 사용 : 킬 목표
	auto target = GetWorld()->GetFirstPlayerController()->GetPawn();
	AProjectDCharacter* player = Cast<AProjectDCharacter>( target );
	player->OnObjectiveIDCalled.Broadcast( "Boss" , 1 );

	//this->Destroy();
}





