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
	//원거리 몬스터 기본 설정
	this->maxHP = 150;
	this->AttackRange = 800;
	anim = Cast<UMonsterAnim>( this->GetMesh()->GetAnimInstance() );
}



void ARangedMonster::AttackState()
{
	//Super::AttackState();

	GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "ARangedMonster::AttackState()" ) );

	
	anim->animState = MonsterFSM->state;

	currentTime += GetWorld()->GetDeltaSeconds();
	if(currentTime>attackDelayTime)
	{
		anim->bAttackDelay = true;
		currentTime = 0;
	}
	
	anim->bAttackDelay = false;
	MoveToTarget();
	

	if (TargetVector.Size() > AttackRange) {
		MonsterFSM->state = EMonsterState::Move;
	}
}
