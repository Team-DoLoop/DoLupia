// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/StrikeMonster.h"

#include "Characters/ProjectDCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Monsters/MonsterSword.h"
#include "Monsters/MonsterFSM.h"


AStrikeMonster::AStrikeMonster()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh>MonsterMesh( TEXT( "/Game/Asset/Character/Sword_Robot/Sword_Robot.Sword_Robot" ) );
	RootComponent->SetWorldScale3D( FVector( 1.5f ) );
	if (MonsterMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh( MonsterMesh.Object );
		GetMesh()->SetRelativeLocationAndRotation( FVector( 0 , 0 , -189 ) , FRotator( 0 , -90 , 0 ) );

	}

	SwordCollision = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "SwordCollision" ) );

	FName WeaponSocket( TEXT( "hand_rSocket" ) );
	if (GetMesh()->DoesSocketExist( WeaponSocket ))
	{
		SwordCollision->SetupAttachment( GetMesh() , WeaponSocket );
	}


	/*if (GetMesh()->DoesSocketExist( WeaponSocket ))
	{
		Weapon = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "Weapon" ) );
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SK_WEAPON( TEXT( "/Game/Monsters/TrashMonster/Assets/Weapon/Swords_Group_ThinSword_Mesh.Swords_Group_ThinSword_Mesh" ) );
		if (SK_WEAPON.Succeeded())
		{
			Weapon->SetStaticMesh( SK_WEAPON.Object );
		}
		Weapon->SetupAttachment( GetMesh() , WeaponSocket );
	}*/

	
	ConstructorHelpers::FClassFinder<UAnimInstance>tempClass( TEXT( "AnimBlueprint'/Game/Monsters/TrashMonster/Blueprints/ABP_StrikeMonster1.ABP_StrikeMonster1_C'" ) );
	if (tempClass.Succeeded()) 
	{
		GetMesh()->SetAnimInstanceClass( tempClass.Class );
	}

}

void AStrikeMonster::BeginPlay()
{
	Super::BeginPlay();
	this->MonsterType= EMonsterType::Strike;
	this->MonsterFSM->state = EMonsterState::Idle;
	//근거리 몬스터 체력 설정
	this->maxHP = 150;
	UE_LOG( LogTemp , Warning , TEXT( "%d" ) , this->maxHP );

	SwordCollision->OnComponentBeginOverlap.AddDynamic( this , &AStrikeMonster::OnMyCompBeginOverlap );
}


void AStrikeMonster::OnMyCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AProjectDCharacter* OverlapPlayer = Cast<AProjectDCharacter>( OtherActor )) {

		if (OverlapPlayer->GetController())
		{
			GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "AStrikeMonster::플레이어 공격 성공!!" ) );
			OverlapPlayer->TakeHit( EAttackType::BASIC, 30 );

			return;
		}

		//플레이어 Damage 처리
		UE_LOG( LogTemp , Warning , TEXT( "!OverlapPlayer->GetController()" ) );

	}
}

void AStrikeMonster::AttackState()
{
	Super::AttackState();
	//GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "AStrikeMonster::AttackState()" ) );
}


