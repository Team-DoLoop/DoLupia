// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/Drone/BossDroneLaser.h"

#include "NiagaraFunctionLibrary.h"
#include "Characters/ProjectDCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Monsters/BossMonster.h"
#include "Monsters/Drone/BossDrone.h"

// Sets default values
ABossDroneLaser::ABossDroneLaser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    DumpSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Dump"));
    SetRootComponent( DumpSceneComponent );

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Laser Mesh"));
	StaticMeshComponent->SetupAttachment(DumpSceneComponent);

    Speed = 3000.f;
}

// Called when the game starts or when spawned
void ABossDroneLaser::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ABossDroneLaser::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    MoveLaser(DeltaTime);
}

void ABossDroneLaser::Initialize( ABossDrone* MyDrone )
{
    Drone = MyDrone;
    CurrentLocation = Drone->GetActorLocation();
    SetActorLocation( CurrentLocation );
}

void ABossDroneLaser::Initialize(const FVector& InDirection, float InSpeed)
{
    Direction = InDirection.GetSafeNormal();
    Speed = InSpeed;
}

void ABossDroneLaser::MoveLaser(float DeltaTime)
{

    SpeedLocation += (Direction * Speed * DeltaTime);
    FVector NextLocation = CurrentLocation + SpeedLocation;

    //if(LaserNiagaraSystem)
    //{
    //    UNiagaraFunctionLibrary::SpawnSystemAtLocation
    //	(
		  //  GetWorld(),
		  //  LaserNiagaraSystem,
		  //  CurrentLocation
    //    );
    //}


    FHitResult HitResult;
    FCollisionQueryParams Params;

    Params.AddIgnoredActor( this );
    Params.AddIgnoredActor( UGameplayStatics::GetActorOfClass( GetWorld(), ABossMonster::StaticClass() ) );
    Params.AddIgnoredActor( UGameplayStatics::GetActorOfClass( GetWorld(), AProjectDCharacter::StaticClass()) );
    Params.AddIgnoredActor( Drone );


    // Raycast를 사용하여 이동 경로 상의 충돌을 검사
    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult ,
        CurrentLocation ,
        NextLocation ,
        ECC_Visibility ,
        Params
    );

    //DrawDebugLine(GetWorld(), CurrentLocation, NextLocation, FColor::Black);

    // 충돌하지 않은 경우 레이저를 다음 위치로 이동
    //CurrentLocation = NextLocation;
    //SetActorLocation( CurrentLocation );

    if (bHit)
    {
        OnHit( nullptr , HitResult.GetActor() , HitResult.GetComponent() , FVector::ZeroVector , HitResult );
    }
    else
    {
        // 충돌하지 않은 경우 레이저를 다음 위치로 이동
        CurrentLocation = NextLocation;
        SetActorLocation( CurrentLocation );
    }
}



void ABossDroneLaser::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                            FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor && OtherActor != this && OtherComp)
	{
		
	}
}

