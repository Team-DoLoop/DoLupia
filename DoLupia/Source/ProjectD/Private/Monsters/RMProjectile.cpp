// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/RMProjectile.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Characters/ProjectDCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Monsters/DamageTestActor.h"

// Sets default values
ARMProjectile::ARMProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>( TEXT( "CollisionComponent" ) );
	SetRootComponent( CollisionComponent );
	CollisionComponent->SetGenerateOverlapEvents( true );

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "meshComp" ) );
	meshComp->SetupAttachment( RootComponent );
	meshComp->SetCollisionEnabled( ECollisionEnabled::QueryAndPhysics );
}

// Called when the game starts or when spawned
void ARMProjectile::BeginPlay()
{
	Super::BeginPlay();

	// FFileHelper 클래스를 이용하여 로그 파일 생성
	FString FilePath = FPaths::ProjectLogDir() + TEXT( "LogFileName.log" );
	FFileHelper::SaveStringToFile( L"ARMProjectile::BeginPlay -> Start" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );

	CollisionComponent->OnComponentBeginOverlap.AddDynamic( this , &ARMProjectile::OnMyCompBeginOverlap );


	FFileHelper::SaveStringToFile( L"ARMProjectile::BeginPlay -> End" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );
}

// Called every frame
void ARMProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector dir = GetActorForwardVector();
	FVector P0 = GetActorLocation();
	FVector vt = dir * speed * GetWorld()->GetDeltaSeconds();
	SetActorLocation( P0 + vt );
}

void ARMProjectile::OnMyCompBeginOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
{
	if (AProjectDCharacter* OverlapPlayer = Cast<AProjectDCharacter>( OtherActor )) {

		if (OverlapPlayer->GetController())
		{
			//GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "ARMProjectile::플레이어 공격 성공!!" ) );
			OverlapPlayer->TakeHit( EAttackType::BASIC , EEffectAttackType::NONE , 30 );
			UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , expVFX , this->GetActorLocation() );
			this->Destroy();
			return;
		}

	}

	if (ADamageTestActor* DamageTestActor = Cast<ADamageTestActor>( OtherActor )) {

		if (DamageTestActor)
		{
			UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , expVFX , this->GetActorLocation() );

			this->Destroy();
			return;
		}
	}
}


