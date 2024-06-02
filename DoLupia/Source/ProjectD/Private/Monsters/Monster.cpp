﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/Monster.h"

#include "AIController.h"
#include "Monsters/MonsterFSM.h"
#include "Monsters/MonsterHPWidget.h"
#include <NavigationSystem.h>
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/SkeletalMesh.h"
#include "Characters/ProjectDCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Items/Sword/SwordBase.h"
#include "Monsters/MonsterAnim.h"
#include "Navigation/PathFollowingComponent.h"
#include "Spawner/ItemSpawner.h"
// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	MonsterFSM = CreateDefaultSubobject<UMonsterFSM>(TEXT("MonsterFSM"));

	healthUI = CreateDefaultSubobject<UWidgetComponent>( TEXT( "healthUI" ) );

	healthUI->SetupAttachment( RootComponent );
	healthUI->SetCastShadow( false );

}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	int32 yaw = rand() % 360;
	SetActorRotation( FRotator( 0 , yaw ,0 ) );
	monsterHPWidget = Cast<UMonsterHPWidget>( healthUI->GetWidget() );

	anim = Cast<UMonsterAnim>( this->GetMesh()->GetAnimInstance() );

	ai = Cast<AAIController>( this->GetController() );

	IsAlive = true;

	if(!ItemSpawner)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.bNoFail = true;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		const FVector& SpawnLocation{ GetActorLocation() + (GetActorForwardVector() * 50.f) + FVector(0.0, 0.0, 200.0)};
		const FTransform SpawnTransform( GetActorRotation() , SpawnLocation );

		ItemSpawner = GetWorld()->SpawnActor<AItemSpawner>( AItemSpawner::StaticClass() , SpawnTransform , SpawnParams );
		ItemSpawner->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

		if(ItemSpawner)
		{
			for (auto& elem : ItemTuples)
			{
				ItemSpawner->EditItemSpawnerInfo( elem );
				ItemSpawner->CreateItem( elem.ItemName , elem.DropPercentage );
			}
		}
	}

}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsAlive)
	{
		//HP Widget 빌보드 처리
		FVector camLoc = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
		FVector dir = camLoc - healthUI->GetComponentLocation();
		dir.Normalize();
		healthUI->SetWorldRotation( dir.ToOrientationRotator() );

		//항상 플레이어를 바라보도록 회전
		FVector rot = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - this->GetActorLocation();
		rot.Normalize();
		if (bHasTarget)
		{
			this->SetActorRotation( rot.ToOrientationRotator() );
		}
	}
}

void AMonster::OnMyCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}


void AMonster::IdleState()
{
	//애니메이션 상태 업데이트
	anim->animState = MonsterFSM->state;

	//플레이어를 타겟으로 설정
	target = GetWorld()->GetFirstPlayerController()->GetPawn();
	TargetVector = target->GetActorLocation() - this->GetActorLocation();
	if (TargetVector.Size() < TargetRange) {
		MonsterFSM->state = EMonsterState::Move;
		anim->animState = MonsterFSM->state;
		bHasTarget = true;
	}
}



void AMonster::MoveState()
{
	if (currentHP <= 0)
	{
		UE_LOG( LogTemp , Warning , TEXT( "AMonster::MoveState()  currentHP <= 0" ) )

		return;
	}
	//GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "AMonster::MoveState()" ) );

	//플레이어 방향으로 이동
	MoveToTarget();

	if (TargetVector.Size() < AttackRange) {
		ai->StopMovement();
		MonsterFSM->state = EMonsterState::Attack;
		anim->animState = MonsterFSM->state;
		anim->bAttackDelay = true;
		currentTime = attackDelayTime;
	}
}

void AMonster::AttackState()
{
	if (target == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("AMonster::AttackState()  target == nullptr"))
		return;
	}

	if(currentHP<=0)
	{
		return;
	}
	GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "AMonster::AttackState()" ) );
	currentTime += GetWorld()->GetDeltaSeconds();
	TargetVector = target->GetActorLocation() - this->GetActorLocation();

	//공격 개시
	if(currentTime>attackDelayTime)
	{
		currentTime = 0;
		anim->bAttackDelay = true;
	}

	//공격 범위를 벗어나고 && 하던 공격이 완료되었다면
	if (TargetVector.Size() > AttackRange && anim->bIsAttackComplete) {
		MonsterFSM->state = EMonsterState::Move;
		anim->animState = MonsterFSM->state;
		anim->bIsAttackComplete = false;
	}

}

void AMonster::DamageState()
{
	//GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "AMonster::DamageState()" ) );
	anim->animState = MonsterFSM->state;

	currentTime += GetWorld()->GetDeltaSeconds();
	if (currentTime > 1.5)
	{
		MonsterFSM->state = EMonsterState::Move;
		GetCapsuleComponent()->SetCollisionEnabled( ECollisionEnabled::QueryAndPhysics );
		currentTime = 0;
		anim->animState = MonsterFSM->state;
	}

}

void AMonster::DieState()
{
	//GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "AMonster::DieState()" ) );
	IsAlive = false;
	anim->animState = MonsterFSM->state;
	this->GetCapsuleComponent()->SetCollisionEnabled( ECollisionEnabled::NoCollision );
	if(healthUI)
	{
		healthUI->DestroyComponent();
	}
}

void AMonster::MoveToTarget()
{
	FRotator MonsterRotation = FRotationMatrix::MakeFromX( TargetVector ).Rotator();
	this->SetActorRotation( MonsterRotation );
	target = GetWorld()->GetFirstPlayerController()->GetPawn();
	FVector destination = target->GetActorLocation();
	TargetVector = destination - this->GetActorLocation();
	//this->AddMovementInput( TargetVector.GetSafeNormal() );

	auto ns = UNavigationSystemV1::GetNavigationSystem( GetWorld() );
	if (ns == nullptr)
	{
		GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Red , TEXT( "Navigation System not found" ) );
		return;
	}

	ai = Cast<AAIController>( GetController() );
	if (ai == nullptr)
	{
		GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Red , TEXT( "AI Controller not found" ) );
		return;
	}

	// 이동 요청 생성 및 설정
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalLocation( destination );
	MoveRequest.SetAcceptanceRadius( 10.0f );

	// 경로 찾기 쿼리 생성 및 설정
	FPathFindingQuery Query;
	ai->BuildPathfindingQuery( MoveRequest , Query );

	// 경로 찾기 결과
	FPathFindingResult PathResult = ns->FindPathSync( Query );
	if (PathResult.IsSuccessful())
	{
		ai->MoveToLocation( destination );
		GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "AMonster::MoveToTarget()" ) );
	}
	else
	{
		GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Red , TEXT( "Pathfinding failed" ) );
	}
}

void AMonster::OnMyTakeDamage(int32 damage)
{
	
	currentHP -= damage;

	if (currentHP < 0)
	{
		currentHP = 0;
	}

	if (currentHP > 0)
	{
		MonsterFSM->state = EMonsterState::Damage;
	}

	else
	{
		MonsterFSM->state = EMonsterState::Die;
	}

	monsterHPWidget->SetHP( currentHP , maxHP );
	UE_LOG( LogTemp , Warning , TEXT( "currentHP : %d" ) , currentHP );

	// 충돌체 끄기
	GetCapsuleComponent()->SetCollisionEnabled( ECollisionEnabled::NoCollision );
	ai->StopMovement();

}

void AMonster::DestroyMonster()
{
	//죽음 애니메이션 끝난 후 destroy (AnimNotify에서 호출)
	
	//플레이어 델리게이트 사용 : 킬 목표
	AProjectDCharacter* player = Cast<AProjectDCharacter>( target );
	FString EnumValueAsString = EnumToString( EMonsterType::Strike );
	player->OnObjectiveIDCalled.Broadcast( EnumValueAsString , 1 );

	//아이템 드랍
	if (ItemSpawner)
		ItemSpawner->SpawnItem( ItemSpawner );

	this->Destroy();
		
}

bool AMonster::GetRandomPositionInNavMesh(FVector centerLocation, float radius, FVector& dest)
{
	auto ns = UNavigationSystemV1::GetNavigationSystem( GetWorld() );
	FNavLocation loc;
	bool result = ns->GetRandomReachablePointInRadius( centerLocation , radius , loc );
	dest = loc.Location;
	return result;

}

