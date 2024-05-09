// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/StrikeMonster.h"



AStrikeMonster::AStrikeMonster()
{
	FName WeaponSocket( TEXT( "hand_rSocket" ) );
	if (GetMesh()->DoesSocketExist( WeaponSocket ))
	{
		Weapon = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "Weapon" ) );
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SK_WEAPON( TEXT( "/Game/Monsters/Assets/Weapon/Swords_Group_ThinSword_Mesh.Swords_Group_ThinSword_Mesh" ) );
		if (SK_WEAPON.Succeeded())
		{
			Weapon->SetStaticMesh( SK_WEAPON.Object );
		}
		Weapon->SetupAttachment( GetMesh() , WeaponSocket );
	}


}

void AStrikeMonster::BeginPlay()
{
	Super::BeginPlay();
	this->MonsterType= EMonsterType::Strike;
	//근거리 몬스터 체력 설정
	this->maxHP = 150;
	UE_LOG( LogTemp , Warning , TEXT( "%d" ) , this->maxHP );
}

void AStrikeMonster::AttackState()
{
	Super::AttackState();
	GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "AStrikeMonster::AttackState()" ) );
}


