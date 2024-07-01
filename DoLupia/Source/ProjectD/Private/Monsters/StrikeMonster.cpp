﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/StrikeMonster.h"
#include "Characters/ProjectDCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Gamemode/PlayerGameMode.h"
#include "Monsters/MonsterFSM.h"
#include "Monsters/MonsterHPWidget.h"


AStrikeMonster::AStrikeMonster()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh>MonsterMesh( TEXT( "/Game/Asset/Character/Sword_Robot/Sword_Robot.Sword_Robot" ) );
	RootComponent->SetWorldScale3D( FVector( 1.5f ) );
	if (MonsterMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh( MonsterMesh.Object );
		GetMesh()->SetRelativeLocationAndRotation( FVector( 0 , 0 , -189 ) , FRotator( 0 , -90 , 0 ) );

	}

	FName WeaponSocket( TEXT( "WeaponSocket" ) );
	if (GetMesh()->DoesSocketExist( WeaponSocket ))
	{
		Weapon = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "Weapon" ) );
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SK_WEAPON( TEXT( "/Game/Monsters/TrashMonster/Assets/SM_Baton.SM_Baton" ) );
		if (SK_WEAPON.Succeeded())
		{
			Weapon->SetStaticMesh( SK_WEAPON.Object );
		}
		Weapon->SetupAttachment( GetMesh() , WeaponSocket );
		Weapon -> SetCollisionEnabled( ECollisionEnabled::QueryAndPhysics );
		Weapon->SetGenerateOverlapEvents( true );
	}

	
	ConstructorHelpers::FClassFinder<UAnimInstance>tempClass( TEXT( "AnimBlueprint'/Game/Monsters/TrashMonster/Blueprints/ABP_StrikeMonster1.ABP_StrikeMonster1_C'" ) );
	if (tempClass.Succeeded()) 
	{
		GetMesh()->SetAnimInstanceClass( tempClass.Class );
	}

	
}

void AStrikeMonster::BeginPlay()
{
	Super::BeginPlay();

	// FFileHelper 클래스를 이용하여 로그 파일 생성
	FString FilePath = FPaths::ProjectLogDir() + TEXT( "LogFileName.log" );
	FFileHelper::SaveStringToFile( L"AStrikeMonster::BeginPlay -> Start" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );

	this->MonsterType= EMonsterType::Strike;
	this->MonsterFSM->state = EMonsterState::Idle;


	//근거리 몬스터 체력 설정
	if (GM->GetLevelIdx() == 1)
	{
		maxHP = 15;
		currentHP = maxHP;
	}
	if (GM->GetLevelIdx() == 2)
	{
		maxHP = 30;
		currentHP = maxHP;
	}

	FFileHelper::SaveStringToFile( L"AStrikeMonster::BeginPlay -> End" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );

	Weapon->OnComponentBeginOverlap.AddDynamic( this , &AStrikeMonster::OnMyCompBeginOverlap );
}





void AStrikeMonster::OnMyCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AProjectDCharacter* OverlapPlayer = Cast<AProjectDCharacter>( OtherActor )) {

		if (OverlapPlayer->GetController())
		{
			if(IsCollisionEnabled)
			{
				OverlapPlayer->TakeHit( EAttackType::BASIC , EEffectAttackType::NONE , 10 );
				IsCollisionEnabled = false;
			}
		}
	}
}

void AStrikeMonster::AttackState()
{
	Super::AttackState();
	//GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "AStrikeMonster::AttackState()" ) );
}





