﻿// Fill out your copyright notice in the Description page of Project Settings.


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

	me = Cast<AMonster>(GetOwner());
	
	state = EMonsterState::Patrol;
}


// Called every frame
void UMonsterFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (state)
	{
	case EMonsterState::Patrol:		me->PatrolState();		break;
	case EMonsterState::Move:		me->MoveState();		break;
	case EMonsterState::Attack:		me->AttackState();		break;
	case EMonsterState::Damage:		me->DamageState();		break;
	case EMonsterState::Die:		me->DieState();			break;
	}
}


