// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/RangedMonster.h"

#include "AIController.h"
#include "Characters/ProjectDCharacter.h"
#include "Components/ArrowComponent.h"
#include "Monsters/MonsterAnim.h"
#include "Monsters/MonsterFSM.h"
#include "Monsters/RMProjectile.h"

ARangedMonster::ARangedMonster()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh>MonsterMesh( TEXT( "/Game/Asset/Character/Spider_Robot/Spider3/Spider_Robot_3.Spider_Robot_3" ) );
	RootComponent->SetWorldScale3D( FVector( 1.5f ) );
	if (MonsterMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh( MonsterMesh.Object );
		//GetMesh()->SetRelativeLocationAndRotation( FVector( 0 , 0 , -189 ) , FRotator( 0 , -90 , 0 ) );

	}

	ConstructorHelpers::FClassFinder<UAnimInstance>tempClass( TEXT( "AnimBlueprint'/Game/Monsters/TrashMonster/Blueprints/ABP_RangedMonster1.ABP_RangedMonster1_C'" ) );
	if (tempClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass( tempClass.Class );
	}

	firePosition = CreateDefaultSubobject<UArrowComponent>( TEXT( "firePosition" ) );
	firePosition->SetupAttachment( RootComponent );
}

void ARangedMonster::BeginPlay()
{
	Super::BeginPlay();

	// FFileHelper 클래스를 이용하여 로그 파일 생성
	FString FilePath = FPaths::ProjectLogDir() + TEXT( "LogFileName.log" );
	FFileHelper::SaveStringToFile( L"ARangedMonster::BeginPlay -> Start" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );

	this->MonsterType = EMonsterType::Ranged;
	MonsterFSM->state = EMonsterState::Idle;
	//원거리 몬스터 기본 설정
	maxHP = 30;
	currentHP = maxHP;
	this->AttackRange = 1200;
	this->attackDelayTime = 3;
	anim = Cast<UMonsterAnim>( this->GetMesh()->GetAnimInstance() );

	FFileHelper::SaveStringToFile( L"ARangedMonster::BeginPlay -> End" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );
}


void ARangedMonster::MoveState()
{
	//Super::MoveState();
	//GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "ARangedMonster::MoveState()" ) );

	MoveToTarget();
	
	if (TargetVector.Size() < AttackRange) {
		if(HasObstacle())
		{
			ai->StopMovement();
			MonsterFSM->state = EMonsterState::Attack;
			anim->animState = MonsterFSM->state;
			anim->bAttackDelay = true;
			currentTime = attackDelayTime;
			//UE_LOG( LogTemp , Warning , TEXT( "장애물 없어서 공격모드로 넘어갈게요" )  );
			
		}
		else
		{
			MoveToTarget();
			//UE_LOG( LogTemp , Warning , TEXT( "공격범위안에 있지만 장애물 있어서 이동할게요" ) );
		}
		
	}
}

void ARangedMonster::AttackState()
{
	//Super::AttackState();
	//GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "ARangedMonster::AttackState()" ) );

	currentTimeRM += GetWorld()->GetDeltaSeconds();
	TargetVector = target->GetActorLocation() - this->GetActorLocation();
	if(currentTimeRM > attackDelayTime)
	{
		if (HasObstacle())
		{
			currentTimeRM = 0;
			anim->bAttackDelay = true;
			bStartToAttack = false;
			//UE_LOG( LogTemp , Warning , TEXT( "장애물 없어서 공격하고 있어요" ) );
		}
		else
		{
			MonsterFSM->state = EMonsterState::Move;
			anim->animState = MonsterFSM->state;
			//UE_LOG( LogTemp , Warning , TEXT( "공격모드인데 장애물 있어서 이동모드로 전환할게요" ) );

		}
	}
	

	if (TargetVector.Size() > AttackRange && anim->bIsAttackComplete) {
			MonsterFSM->state = EMonsterState::Move;
			anim->animState = MonsterFSM->state;
			anim->bIsAttackComplete = false;
			//UE_LOG( LogTemp , Warning , TEXT( "공격범위 벗어나서 이동모드로 넘어갈게요" ) );
	}
	

}

void ARangedMonster::RangedAttack()
{
	// notify 시점에 투사체 발사, 
	// 만약 플레이어와 충돌하면 플레이어 hp 감소
	// 10초 뒤 투사체 파괴
	//GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "ARangedMonster::Attack()" ) );

	if(ProjectileClass)
	{
		FTransform t = firePosition->GetComponentTransform();
		GetWorld()->SpawnActor<ARMProjectile>( ProjectileClass , t );
	}
}

bool ARangedMonster::HasObstacle()
{
	FHitResult outHit;

	FVector Start = this->GetActorLocation(); // 레이캐스트의 시작점
	FVector End = Start + this->GetActorForwardVector() * 100000; // 레이캐스트의 종료점

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor( this ); // 현재 액터는 충돌 검사에서 무시

	// 레이캐스트를 수행하고 충돌 정보를 outHit에 저장.
	bool bIsHit = GetWorld()->LineTraceSingleByChannel( outHit , Start , End , ECC_GameTraceChannel9 , CollisionParams );

	/*if (bIsHit)
	{
		DrawDebugLine( GetWorld() , Start , End , FColor::Red , false , 0.1f , 0 , 5.f );
		UE_LOG( LogTemp , Warning , TEXT( "Obstacle detected!" ) );
	}
	else
	{
		DrawDebugLine( GetWorld() , Start , End , FColor::Green , false , 0.1f , 0 , 5.f );
		UE_LOG( LogTemp , Warning , TEXT( "No Obstacle detected!" ) );
	}*/


	if (bIsHit)
	{
		// 충돌한 액터를 처리
		AActor* HitActor = outHit.GetActor();
		if (HitActor)
		{
			// 충돌한 액터가 플레이어라면
			AProjectDCharacter* player = Cast<AProjectDCharacter>( HitActor );
			if (player)
			{
				//RangedAttack();
				bStartToAttack= true;
			
			}
			else
			{
				bStartToAttack = false;
			}
		}
	}
	return bStartToAttack;

}
