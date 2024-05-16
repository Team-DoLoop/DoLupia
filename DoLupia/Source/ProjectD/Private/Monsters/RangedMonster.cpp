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
	FName WeaponSocket( TEXT( "hand_rSocket" ) );
	if (GetMesh()->DoesSocketExist( WeaponSocket ))
	{
		Weapon = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "Weapon" ) );
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SK_WEAPON( TEXT( "/Game/Monsters/Assets/Weapon/Swords_Group_MeteorSword_Mesh.Swords_Group_MeteorSword_Mesh" ) );
		if (SK_WEAPON.Succeeded())
		{
			Weapon->SetStaticMesh( SK_WEAPON.Object );
		}
		Weapon->SetupAttachment( GetMesh() , WeaponSocket );
	}

	ConstructorHelpers::FClassFinder<UAnimInstance>tempClass( TEXT( "AnimBlueprint'/Game/Monsters/Blueprints/ABP_RangedMonster.ABP_RangedMonster_C'" ) );
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

	this->MonsterType = EMonsterType::Ranged;
	MonsterFSM->state = EMonsterState::Idle;
	//원거리 몬스터 기본 설정
	this->maxHP = 150;
	this->AttackRange = 1000;
	this->attackDelayTime = 3;
	anim = Cast<UMonsterAnim>( this->GetMesh()->GetAnimInstance() );
	UE_LOG( LogTemp , Warning , TEXT( "%f" ) , attackDelayTime );
}


void ARangedMonster::MoveState()
{
	//Super::MoveState();

	MoveToTarget();

	if (TargetVector.Size() < AttackRange) {
		if(HasObstacle())
		{
			ai->StopMovement();
			MonsterFSM->state = EMonsterState::Attack;
			anim->animState = MonsterFSM->state;
			anim->bAttackDelay = true;
			currentTime = attackDelayTime;
		}
		
	}
}

void ARangedMonster::AttackState()
{
	//Super::AttackState();

	//GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "ARangedMonster::AttackState()" ) );
	currentTimeRM += GetWorld()->GetDeltaSeconds();
	TargetVector = target->GetActorLocation() - this->GetActorLocation();
	bHasTarget = false;

	if (currentTimeRM > attackDelayTime)
	{
		currentTimeRM = 0;
		anim->bAttackDelay = true;
		bOnceAttack = true;
		bHasTarget = true;
	}

	if (bOnceAttack)
	{
		if (TargetVector.Size() > AttackRange) {
			MonsterFSM->state = EMonsterState::Move;
			anim->animState = MonsterFSM->state;
			bOnceAttack = false;
		}
	}

}

void ARangedMonster::RangedAttack()
{
	// notify 시점에 투사체 발사, 
	// 만약 플레이어와 충돌하면 플레이어 hp 감소
	// 10초 뒤 투사체 파괴
	//GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "ARangedMonster::MagicAttack()" ) );

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
	bool bIsHit = GetWorld()->LineTraceSingleByChannel( outHit , Start , End , ECC_Visibility , CollisionParams );

	if (bIsHit)
	{
		DrawDebugLine( GetWorld() , Start , End , FColor::Red , false , 0.1f , 0 , 5.f );
		UE_LOG( LogTemp , Warning , TEXT( "Obstacle detected!" ) );
	}
	else
	{
		DrawDebugLine( GetWorld() , Start , End , FColor::Green , false , 0.1f , 0 , 5.f );
		UE_LOG( LogTemp , Warning , TEXT( "No Obstacle detected!" ) );
	}


	if (bIsHit)
	{
		// 충돌한 액터를 처리
		AActor* HitActor = outHit.GetActor();
		if (HitActor)
		{
			// 충돌한 액터가 플레이어가 아니라면
			AProjectDCharacter* player = Cast<AProjectDCharacter>( HitActor );
			if (player)
			{
				//RangedAttack();
				bStartToAttack= true;
			}
			else
			{
				//PatrolState로 전환
				/*MonsterFSM->state = EMonsterState::Move;
				anim->animState = MonsterFSM->state;*/
				bStartToAttack = false;
			}
		}
	}
	return bStartToAttack;

}
