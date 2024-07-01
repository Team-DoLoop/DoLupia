// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Skill/PlayerSkillWaterBlade.h"

#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"
#include "Monsters/BossMonster.h"
#include "Monsters/Monster.h"

APlayerSkillWaterBlade::APlayerSkillWaterBlade()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetBoxExtent(FVector(130.0f, 200.0f, 20.0f));
	SetRootComponent(BoxComp);
	
	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));
	NiagaraComp->SetWorldScale3D(FVector(1.0f));
	NiagaraComp->SetRelativeLocation(FVector(-95.0f, 25.0f, 0.0f));
	NiagaraComp->SetRelativeRotation(FRotator(0.0f,210.0f,.0f));
	NiagaraComp->SetupAttachment(RootComponent);

}

void APlayerSkillWaterBlade::BeginPlay()
{
	Super::BeginPlay();

	// FFileHelper 클래스를 이용하여 로그 파일 생성
	FString FilePath = FPaths::ProjectLogDir() + TEXT( "LogFileName.log" );
	FFileHelper::SaveStringToFile( L"APlayerSkillWaterBlade::BeginPlay -> Start" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );

	SetActorRotation(Rot);

	BoxComp->SetHiddenInGame(!bIsShowDebugLine);

	FFileHelper::SaveStringToFile( L"APlayerSkillWaterBlade::BeginPlay -> End" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );
}

void APlayerSkillWaterBlade::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector P0 = this->GetActorLocation ( );
	FVector vt = Direction * Speed * DeltaSeconds;

	SetActorLocation ( P0 + vt );
}

void APlayerSkillWaterBlade::ActivateSkill()
{
	Super::ActivateSkill();
}

void APlayerSkillWaterBlade::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if(AMonster* MonsterActor = Cast<AMonster>(OtherActor))
	{
		MonsterActor->OnMyTakeDamage(SkillDamage);
	}

	else if(ABossMonster* BossMonster = Cast<ABossMonster>(OtherActor))
	{
		BossMonster->OnMyTakeDamage(SkillDamage);
	}
	
}
