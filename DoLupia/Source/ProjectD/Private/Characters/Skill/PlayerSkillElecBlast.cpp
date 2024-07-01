﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Skill/PlayerSkillElecBlast.h"

#include "NiagaraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Monsters/BossMonster.h"
#include "Monsters/Monster.h"

class ABossMonster;

APlayerSkillElecBlast::APlayerSkillElecBlast()
{
	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));
	NiagaraComp->SetWorldScale3D(FVector(1.0f));
	SetRootComponent(NiagaraComp);
}

void APlayerSkillElecBlast::BeginPlay()
{
	Super::BeginPlay();

	// FFileHelper 클래스를 이용하여 로그 파일 생성
	FString FilePath = FPaths::ProjectLogDir() + TEXT( "LogFileName.log" );
	FFileHelper::SaveStringToFile( L"APlayerSkillElecBlast::BeginPlay -> Start" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );

	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]() {
	ActivateSkill();
}, 0.3f, false);

	FFileHelper::SaveStringToFile( L"APlayerSkillElecBlast::BeginPlay -> End" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );
}

void APlayerSkillElecBlast::ActivateSkill()
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
				UE_LOG(LogTemp, Log, TEXT("ElecBlast Attack %s Monster : %d"), *Monster->GetName(), SkillDamage);
			}
		}
		
		else if (ABossMonster* BossMonster = Cast<ABossMonster>(TargetActor))
		{
			if (BossMonster)
			{
				BossMonster->OnMyTakeDamage(SkillDamage);
				UE_LOG(LogTemp, Log, TEXT("ElecBlast Attack %s Monster : %d"), *BossMonster->GetName(), SkillDamage);
			}
		}
	}
	
	if(bIsShowDebugLine) DrawDebugSphere(GetWorld(), SkillLocation, SkillRadius, 10, FColor::Red, false, SkillVolume);
}
