// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Sword/SwordBase.h"

#include "Characters/ProjectDCharacter.h"
#include "Characters/Components/PlayerFSMComp.h"
#include "Components/CapsuleComponent.h"
#include "Items/ItemBase.h"
#include "Monsters/Monster.h"

// Sets default values
ASwordBase::ASwordBase()
{
	PrimaryActorTick.bCanEverTick = false;

	
	// Collision
	ItemStaticMesh->SetCollisionProfileName("NoCollision");

	collisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("collisionComp"));
	collisionComp->SetupAttachment(RootComponent);
	collisionComp->SetGenerateOverlapEvents(true);
	collisionComp->SetCollisionProfileName(TEXT("Sword"));
	collisionComp->SetRelativeLocation(FVector(0,0, -50));
	collisionComp->SetCapsuleHalfHeight(120.0f);
	collisionComp->SetCapsuleRadius(80.0f);
}

// Called when the game starts or when spawned
void ASwordBase::BeginPlay()
{
	Super::BeginPlay();

	CollisionOff();
}

void ASwordBase::NotifyActorBeginOverlap(AActor* OtherActor)
{

	// 공격 판정 - Player Attack Comp로 이동
	/*
	Super::NotifyActorBeginOverlap(OtherActor);

	AProjectDCharacter* Player = Cast<AProjectDCharacter>(GetAttachParentActor());
	
	// 만약 플레이어에게 들려있다면
	if(Player)
	{
		// 플레이어의 상태가 검 장착 중이라면
		auto PlayerFSM = Player->GetPlayerFSMComp();
		if(PlayerFSM && PlayerFSM->GetCurrentWeaponState() == EPlayerWeaponState::SWORD)
		{
			auto _OtherActor = Cast<AMonster>(OtherActor);
			if(_OtherActor)
			{
				_OtherActor->OnMyTakeDamage(10);
			}
		}
	}
	*/
}

void ASwordBase::CollisionOn()
{
	SetActorEnableCollision(true);
}

void ASwordBase::CollisionOff()
{
	SetActorEnableCollision(false);
}


