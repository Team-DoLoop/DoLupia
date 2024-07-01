// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Skill/PlayerSkillShield.h"

#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "Monsters/BossMonster.h"
#include "Monsters/Monster.h"

APlayerSkillShield::APlayerSkillShield()
{
	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));
	NiagaraComp->SetWorldScale3D(FVector(0.7f));
	SetRootComponent(NiagaraComp);

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetGenerateOverlapEvents ( true );
	SphereComp->SetupAttachment(RootComponent );
	SphereComp->SetSphereRadius(180.0f);
}

void APlayerSkillShield::BeginPlay()
{
	Super::BeginPlay();

	// FFileHelper 클래스를 이용하여 로그 파일 생성
	FString FilePath = FPaths::ProjectLogDir() + TEXT( "LogFileName.log" );
	FFileHelper::SaveStringToFile( L"APlayerSkillShield::BeginPlay -> Start" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );

	SphereComp->SetHiddenInGame(!bIsShowDebugLine);

	FFileHelper::SaveStringToFile( L"APlayerSkillShield::BeginPlay -> End" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );
}

void APlayerSkillShield::ActivateSkill()
{
	Super::ActivateSkill();
	
}

void APlayerSkillShield::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	int32 RandNum = FMath::RandRange(SkillDamage / 2,SkillDamage); // 1~5까지
	if(AMonster* MonsterActor = Cast<AMonster>(OtherActor))
	{
		MonsterActor->OnMyTakeDamage(RandNum);
	}

	else if(ABossMonster* BossMonster = Cast<ABossMonster>(OtherActor))
	{
		BossMonster->OnMyTakeDamage(RandNum);
	}
}
