// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/MonsterFSM.h"

#include "Components/CapsuleComponent.h"
#include "Monsters/Monster.h"
#include "Engine/Engine.h"

// Sets default values for this component's properties
UMonsterFSM::UMonsterFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMonsterFSM::BeginPlay()
{
	Super::BeginPlay();

	// FFileHelper 클래스를 이용하여 로그 파일 생성
	FString FilePath = FPaths::ProjectLogDir() + TEXT( "LogFileName.log" );
	FFileHelper::SaveStringToFile( L"UMonsterFSM::BeginPlay -> Start" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );

	me = Cast<AMonster>(GetOwner());
	
	state = EMonsterState::Idle;

	FFileHelper::SaveStringToFile( L"UMonsterFSM::BeginPlay -> End" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );
}


// Called every frame
void UMonsterFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (state)
	{
	case EMonsterState::Idle:		me->IdleState();		break;
	case EMonsterState::Move:		me->MoveState();		break;
	case EMonsterState::Attack:		me->AttackState();		break;
	case EMonsterState::Damage:		me->DamageState();		break;
	case EMonsterState::Die:		me->DieState();			break;
	}
}


