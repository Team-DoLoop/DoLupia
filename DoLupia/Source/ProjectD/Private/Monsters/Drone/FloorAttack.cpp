﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/Drone/FloorAttack.h"

#include "Characters/ProjectDCharacter.h"
#include "Components/DecalComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AFloorAttack::AFloorAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Attack Component"));
	AttackSphere->SetupAttachment(GetRootComponent());
	AttackSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	AttackSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	AttackSphere->SetSphereRadius( AttackRadius );
	SetRootComponent(AttackSphere);

	// 데칼 컴포넌트 초기화
	DecalComp = CreateDefaultSubobject<UDecalComponent>( TEXT( "DecalComp" ) );
	DecalComp->SetupAttachment( RootComponent );
	DecalComp->DecalSize = FVector( 9.f , AttackRadius , AttackRadius ); 
	DecalComp->SetRelativeRotation( FRotator( 90.0f , 0.0f , 0.0f ) );
}

// Called when the game starts or when spawned
void AFloorAttack::BeginPlay()
{
	Super::BeginPlay();

	// FFileHelper 클래스를 이용하여 로그 파일 생성
	FString FilePath = FPaths::ProjectLogDir() + TEXT( "LogFileName.log" );
	FFileHelper::SaveStringToFile( L"AFA_Blast_Lightning::BeginPlay -> Start" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );


	AttackSphere->SetCollisionEnabled( ECollisionEnabled::Type::NoCollision );
	AttackSphere->OnComponentBeginOverlap.AddDynamic(this, &AFloorAttack::OnSphereOverlap);


	FFileHelper::SaveStringToFile( L"AFA_Blast_LightningAFA_Blast_Lightning::BeginPlay -> End" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );

}

void AFloorAttack::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA<AProjectDCharacter>())
	{
		if (OtherActor && !IgnoerActors.Contains( OtherActor ))
		{
			AProjectDCharacter* Character = Cast<AProjectDCharacter>( OtherActor );

			if(FloorAttackType==EFloorAttackType::BlastFire)
			{
				Character->TakeHit( EAttackType::BASIC , EEffectAttackType::FIRE , 50 );
			}

			if (FloorAttackType == EFloorAttackType::BlastLightening)
			{
				Character->TakeHit( EAttackType::BASIC , EEffectAttackType::ELECTRIC , 50 );

			}
			//FVector Normal = (Character->GetActorLocation() - GetActorLocation()).GetSafeNormal();

			//if(abs(Normal.X) <= 0.05f)
			//{
			//	if(Normal.X <= 0.05f)
			//		Normal.X = 0.1f;
			//	else
			//		Normal.X = 0.1f;
			//}

			//if (abs( Normal.Y ) <= 0.05f)
			//{
			//	if (Normal.Y <= 0.05f)
			//		Normal.Y = 0.1f;
			//	else
			//		Normal.Y = 0.1f;
			//}

			//if (abs( Normal.Z ) <= 0.05f)
			//{
			//	if (Normal.Z <= 0.05f)
			//		Normal.Z = 0.1f;
			//	else
			//		Normal.Z = 0.1f;
			//}

			//Character->LaunchCharacter(FVector(500.f, 500.f, 500.f) * Normal , true, false);
			//IgnoerActors.Add(OtherActor);
		}
	}
}

void AFloorAttack::IgnoreActorsClear()
{
	IgnoerActors.Empty();
}


void AFloorAttack::Trigger()
{
	SpawnAOESphere();
}

// Called every frame
void AFloorAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloorAttack::SpawnAOESphere()
{
#ifdef DEBUG_MY_FLOORATTAK
	const FVector& Location = GetActorLocation();
	const UWorld* World = GetWorld();

	DrawDebugSphere( World , Location , AttackRadius, 12, FColor::Purple);

#endif

	//AttackSphere->SetCollisionEnabled( ECollisionEnabled::Type::QueryAndPhysics );

	//FTimerHandle Handle;

	//GetWorld()->GetTimerManager().SetTimer
	//(
	//	Handle , FTimerDelegate::CreateLambda(
	//		[this]()
	//		{
	//			AttackSphere->SetCollisionEnabled( ECollisionEnabled::Type::QueryAndPhysics );
	//		} ) ,
	//	0.2 , false
	//);

	if(DecalComp)
		DecalComp->DestroyComponent();
}

