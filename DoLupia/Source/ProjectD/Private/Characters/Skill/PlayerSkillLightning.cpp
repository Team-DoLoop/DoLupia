// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Skill/PlayerSkillLightning.h"

#include "NiagaraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Monsters/BossMonster.h"
#include "Monsters/Monster.h"

APlayerSkillLightning::APlayerSkillLightning()
{
	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));
	NiagaraComp->SetWorldScale3D(FVector(1.0f));
	SetRootComponent(NiagaraComp);
}

void APlayerSkillLightning::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]() {
	ActivateSkill();
}, 0.8f, false);
}

void APlayerSkillLightning::ActivateSkill()
{
	Super::ActivateSkill();
	
	FVector SkillLocation = GetActorLocation();

	TArray<AActor*> TargetActors;
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), SkillLocation, SkillRadius,
	TArray<TEnumAsByte<EObjectTypeQuery>>(), nullptr, TArray<AActor*>(),
	TargetActors);
	for(auto TargetActor : TargetActors)
	{
		if (AMonster* Monster = Cast<AMonster>(TargetActor))
		{
			if (Monster)
			{
				Monster->OnMyTakeDamage(SkillDamage);
				UE_LOG(LogTemp, Log, TEXT("Lightning Attack %s Monster : %d"), *Monster->GetName(), SkillDamage);
			}
		}

		else if (ABossMonster* BossMonster = Cast<ABossMonster>(TargetActor))
		{
			if (BossMonster)
			{
				BossMonster->TakeDamage(SkillDamage);
				UE_LOG(LogTemp, Log, TEXT("Lightning Attack %s Monster : %d"), *BossMonster->GetName(), SkillDamage);
			}
		}
	}
	DrawDebugSphere(GetWorld(), SkillLocation, SkillRadius, 10, FColor::Red, false, 0.1f);
}
