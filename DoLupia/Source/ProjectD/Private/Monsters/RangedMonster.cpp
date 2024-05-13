// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/RangedMonster.h"

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
	MonsterFSM->state = EMonsterState::Patrol;
	//원거리 몬스터 기본 설정
	this->maxHP = 150;
	this->AttackRange = 1000;
	this->attackDelayTime = 3;
	anim = Cast<UMonsterAnim>( this->GetMesh()->GetAnimInstance() );
	UE_LOG( LogTemp , Warning , TEXT( "%f" ) , attackDelayTime );
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
	GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "ARangedMonster::MagicAttack()" ) );

	if(ProjectileClass)
	{
		FTransform t = firePosition->GetComponentTransform();
		GetWorld()->SpawnActor<ARMProjectile>( ProjectileClass , t );
	}
}
