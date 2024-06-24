// Fill out your copyright notice in the Description page of Project Settings.


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
#include "GameFramework/CharacterMovementComponent.h"
#include "Gamemode/PlayerGameMode.h"
#include "Items/Sword/SwordBase.h"
#include "Kismet/GameplayStatics.h"
#include "Monsters/MonsterAnim.h"
#include "Monsters/MonsterDamageWidget.h"
#include "Monsters/SpawnMonsterDamage.h"
#include "Monsters/Test_Spawner.h"
#include "Navigation/PathFollowingComponent.h"
#include "Spawner/ItemSpawner.h"

// Sets default values
AMonster::AMonster()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MonsterType = EMonsterType::Strike;
	MonsterFSM = CreateDefaultSubobject<UMonsterFSM>( TEXT( "MonsterFSM" ) );

}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	int32 yaw = rand() % 360;
	SetActorRotation( FRotator( 0 , yaw , 0 ) );

	anim = Cast<UMonsterAnim>( this->GetMesh()->GetAnimInstance() );

	ai = Cast<AAIController>( this->GetController() );

	GM = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );

	IsAlive = true;

	float RandomSpeed = FMath::RandRange( 100.0f , 400.0f );

	// MaxWalkSpeed 설정
	GetCharacterMovement()->MaxWalkSpeed = RandomSpeed;

	target = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ItemSpawner)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.bNoFail = true;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		const FVector& SpawnLocation{ GetActorLocation() + (GetActorForwardVector() * 50.f) + FVector( 0.0, 0.0, 200.0 ) };
		const FTransform SpawnTransform( GetActorRotation() , SpawnLocation );

		ItemSpawner = GetWorld()->SpawnActor<AItemSpawner>( AItemSpawner::StaticClass() , SpawnTransform , SpawnParams );
		ItemSpawner->AttachToActor( this , FAttachmentTransformRules::KeepWorldTransform );

		if (ItemSpawner)
		{
			for (auto& elem : ItemTuples)
			{
				ItemSpawner->EditItemSpawnerInfo( elem );
				ItemSpawner->CreateItem( elem.ItemName , elem.DropPercentage );
			}
		}
	}
	//

	if (GetMesh())
	{
		UMaterialInterface* Material = GetMesh()->GetMaterial( 0 );
		if (Material)
		{
			DynamicDissolveMaterial = UMaterialInstanceDynamic::Create( Material , this );
			GetMesh()->SetMaterial( 0 , DynamicDissolveMaterial );
			DynamicDissolveMaterial->SetScalarParameterValue( "Amount (S)" , 1.f );
		}
	}
}

// Called every frame
void AMonster::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (IsAlive)
	{
		//항상 플레이어를 바라보도록 회전
		FVector rot = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - this->GetActorLocation();
		rot.Normalize();
		if (bHasTarget)
		{
			this->SetActorRotation( rot.ToOrientationRotator() );
		}
	}
}

void AMonster::OnMyCompBeginOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor ,
	UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
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
		UE_LOG( LogTemp , Warning , TEXT( "AMonster::MoveState()  currentHP <= 0" ) );

			return;
	}

	//플레이어 방향으로 이동
	MoveToTarget();

	if (TargetVector.Size() < AttackRange) {

		if (ai && target)
		{
			ai->StopMovement();
			MonsterFSM->state = EMonsterState::Attack;
			anim->animState = MonsterFSM->state;
			anim->bAttackDelay = true;
			currentTime = attackDelayTime;
		}
	}
}

void AMonster::AttackState()
{
	if (target == nullptr)
	{
		UE_LOG( LogTemp , Warning , TEXT( "AMonster::AttackState()  target == nullptr" ) )
			return;
	}

	
	//GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "AMonster::AttackState()" ) );
	currentTime += GetWorld()->GetDeltaSeconds();
	TargetVector = target->GetActorLocation() - this->GetActorLocation();

	//공격 개시
	if (currentTime > attackDelayTime)
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


	
	if (currentHP <= 0 )
	{
		return;
	}
}

void AMonster::DamageState()
{
	//GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "AMonster::DamageState()" ) );
	anim->animState = MonsterFSM->state;

	currentTime += GetWorld()->GetDeltaSeconds();
	if (currentTime > 1.2)
	{
		MonsterFSM->state = EMonsterState::Move;
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
	Amount -= GetWorld()->GetDeltaSeconds() * DissolveSpeed;
	DynamicDissolveMaterial->SetScalarParameterValue( "Amount (S)" , Amount );
}

void AMonster::MoveToTarget()
{
	FVector _destination;

	if (target == nullptr)
	{
		target = GetWorld()->GetFirstPlayerController()->GetPawn();
		UE_LOG( LogTemp , Warning , TEXT( "AMonster::MoveToTarget() target is nullptr" ) );
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "AMonster::MoveToTarget()" ) );
		_destination = target->GetActorLocation();

		if (ai == nullptr)
		{
			UE_LOG( LogTemp , Warning , TEXT( "AMonster::MoveToTarget() AI Controller is nullptr" ) );
			return;
		}
		else
		{
			ai->MoveToLocation( _destination );
			TargetVector = _destination - this->GetActorLocation();
			FRotator MonsterRotation = FRotationMatrix::MakeFromX( TargetVector ).Rotator();
			this->SetActorRotation( MonsterRotation );
		}
	}
}

void AMonster::OnMyTakeDamage( int32 damage )
{

	currentHP -= damage;

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

	//monsterHPWidget->SetHP( currentHP , maxHP );
	

	ai->StopMovement();

}



void AMonster::DestroyMonster()
{
	//죽음 애니메이션 끝난 후 destroy (AnimNotify에서 호출)

	//플레이어 델리게이트 사용 : 킬 목표
	AProjectDCharacter* player = Cast<AProjectDCharacter>( target );
	player->OnObjectiveIDCalled.Broadcast( "Monster" , 1 );

	//아이템 드랍
	if (ItemSpawner)
		ItemSpawner->SpawnItem( ItemSpawner );

	this->Destroy();

}

bool AMonster::GetRandomPositionInNavMesh( FVector centerLocation , float radius , FVector& dest )
{
	auto ns = UNavigationSystemV1::GetNavigationSystem( GetWorld() );
	FNavLocation loc;
	bool result = ns->GetRandomReachablePointInRadius( centerLocation , radius , loc );
	dest = loc.Location;
	return result;

}

//void AMonster::SetActive( bool IsActive )
//{
//	bActive = IsActive;
//	SetActorHiddenInGame( !bActive );
//
//	FTimerHandle TimerHandle;
//	GetWorld()->GetTimerManager().SetTimer( TimerHandle , this , &AMonster::ReturnSelf , 5.0f , false );
//
//}
//
//void AMonster::ReturnSelf()
//{
//	MonsterFSM->state = EMonsterState::Idle;
//	anim->animState = MonsterFSM->state;
//	if (ObjectPool == nullptr) return;
//	ObjectPool->ReturnObject( this );
//	SetActive( false );
//}



