// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/RMProjectile.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Characters/ProjectDCharacter.h"

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

	/*ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>( TEXT( "ProjectileMovementComponent" ) );
	ProjectileMovementComponent->SetUpdatedComponent( CollisionComponent );
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;*/
}

// Called when the game starts or when spawned
void ARMProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->OnComponentBeginOverlap.AddDynamic( this , &ARMProjectile::OnMyCompBeginOverlap );
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
			GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "ARMProjectile::플레이어 공격 성공!!" ) );
			OverlapPlayer->TakeDamage(30);

			return;
		}

		//플레이어 Damage 처리
		UE_LOG( LogTemp , Warning , TEXT( "!OverlapPlayer->GetController()" ) );

	}
}


