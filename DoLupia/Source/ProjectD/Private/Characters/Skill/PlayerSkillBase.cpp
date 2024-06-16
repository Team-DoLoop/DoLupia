// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Skill/PlayerSkillBase.h"

#include "Characters/ProjectDCharacter.h"
#include "Characters/Components/PlayerAttackComp.h"

// Sets default values
APlayerSkillBase::APlayerSkillBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerSkillBase::BeginPlay()
{
	Super::BeginPlay();

	auto Player = Cast<AProjectDCharacter>( GetWorld()->GetFirstPlayerController()->GetCharacter() );
	if(Player)
	{
		if(auto attackComp =  Player->GetAttackComp())
		{
			SkillVolume = attackComp->GetSkillVolume();
		}
	}
}

void APlayerSkillBase::ActivateSkill()
{
}

// Called every frame
void APlayerSkillBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

