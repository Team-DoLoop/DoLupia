// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Skill/PlayerSkillUlt.h"

#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Monsters/Monster.h"

APlayerSkillUlt::APlayerSkillUlt()
{
	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));
	NiagaraComp->SetWorldScale3D(FVector(1.0f));
	SetRootComponent(NiagaraComp);

	/*
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("SphereComp"));
	BoxComp->SetGenerateOverlapEvents ( true );
	BoxComp->SetupAttachment(RootComponent );
	BoxComp->SetBoxExtent(FVector(80.0f, 80.0f, 10.0f));
	BoxComp->SetRelativeScale3D(FVector(7.0f, 7.0f, 5.0f));
	*/
}

void APlayerSkillUlt::BeginPlay()
{
	ApplyDamage(CenterRadius, CenterDamage);
	
	FTimerHandle TimerHandle1;
	FTimerHandle TimerHandle2;
	FTimerHandle TimerHandle3;
	FTimerHandle TimerHandle4;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle1, [this]() {
	ApplyDamage(CenterRadius, CenterDamage); // MidRangeDamage
}, 0.1f, false);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle2, [this]() {
		ApplyDamage(MidRadius, MidDamage); // MidRangeDamage
	}, 0.1f, false);


	GetWorld()->GetTimerManager().SetTimer(TimerHandle3, [this]() {
	ApplyDamage(MidRadius, MidDamage); // MidRangeDamage
}, 0.2f, false);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle4, [this]() {
		ApplyDamage(OuterRadius, OuterDamage); // OuterRangeDamage
	}, 0.2f, false);
	
}

void APlayerSkillUlt::ActivateSkill()
{
	Super::ActivateSkill();
}

/*
void APlayerSkillUlt::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AMonster* MonsterActor = Cast<AMonster>(OtherActor);
	if(MonsterActor)
	{
		MonsterActor->OnMyTakeDamage(Damage);
	}
}
*/


void APlayerSkillUlt::ApplyDamage(float SkillRadius, int32 _Damage)
{
	FVector SkillLocation = GetActorLocation();
	SkillLocation.Z = 0;

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
				Monster->OnMyTakeDamage(_Damage);
				UE_LOG(LogTemp, Log, TEXT("Ult Attack %s Monster : %d"), *Monster->GetName(), _Damage);
			}
		}
	}
	if(CenterRadius == SkillRadius) DrawDebugSphere(GetWorld(), SkillLocation, SkillRadius, 10, FColor::Red, false, 0.1f);
	if(MidRadius == SkillRadius) DrawDebugSphere(GetWorld(), SkillLocation, SkillRadius, 10, FColor::Yellow, false, 0.1f);
	if(OuterRadius == SkillRadius) DrawDebugSphere(GetWorld(), SkillLocation, SkillRadius, 10, FColor::Blue, false, 0.1f);
}
