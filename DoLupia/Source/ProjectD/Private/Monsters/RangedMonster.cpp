// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/RangedMonster.h"

#include "Monsters/MonsterAnim.h"
#include "Monsters/MonsterFSM.h"

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
}

void ARangedMonster::BeginPlay()
{
	Super::BeginPlay();

	this->MonsterType = EMonsterType::Ranged;
	MonsterFSM->state = EMonsterState::Patrol;
	//원거리 몬스터 기본 설정
	this->maxHP = 150;
	this->AttackRange = 1000;
	anim = Cast<UMonsterAnim>( this->GetMesh()->GetAnimInstance() );
}



void ARangedMonster::AttackState()
{
	Super::AttackState();

	GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "ARangedMonster::AttackState()" ) );
	anim->animState = MonsterFSM->state;

	MagicAttack();
	isPaused = true;

	currentTimeRM += GetWorld()->GetDeltaSeconds();
	if (currentTimeRM > attackDelayTime)
	{
		//anim->bAttackDelay = true;
		isPaused = false;
		currentTimeRM = 0;
	}

	/*if(!isPaused)
	{
		MoveToTarget();
	}*/


}

void ARangedMonster::MagicAttack()
{
	// 마법 bullet 발사
	// 만약 플레이어와 충돌하면 플레이어 hp 감소
	// 10초 뒤 bullet 파괴
	GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "ARangedMonster::MagicAttack()" ) );
}
