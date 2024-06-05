// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Skill/PlayerSkillShield.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "Monsters/Monster.h"

APlayerSkillShield::APlayerSkillShield()
{
	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));
	NiagaraComp->SetWorldScale3D(FVector(1.0f));
	SetRootComponent(NiagaraComp);

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetGenerateOverlapEvents ( true );
	SphereComp->SetupAttachment(RootComponent );
	SphereComp->SetSphereRadius(90.0f);
}

void APlayerSkillShield::ActivateSkill()
{
	Super::ActivateSkill();

	
}

void APlayerSkillShield::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AMonster* MonsterActor = Cast<AMonster>(OtherActor);
	if(MonsterActor)
	{
		int32 RandNum = FMath::RandRange(1,6); // 1~5까지
		MonsterActor->OnMyTakeDamage(RandNum);
	}
}
