// Fill out your copyright notice in the Description page of Project Settings.


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
	DecalComp->DecalSize = FVector( AttackRadius , AttackRadius , AttackRadius ); 
	DecalComp->SetRelativeRotation( FRotator( 90.0f , 0.0f , 0.0f ) );
}

// Called when the game starts or when spawned
void AFloorAttack::BeginPlay()
{
	Super::BeginPlay();

	//DecalComp = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMaterial, FVector( AttackRadius , AttackRadius , AttackRadius ), GetActorLocation());

	AttackSphere->SetCollisionEnabled( ECollisionEnabled::Type::NoCollision );
	AttackSphere->OnComponentBeginOverlap.AddDynamic(this, &AFloorAttack::OnSphereOverlap);
}

void AFloorAttack::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA<AProjectDCharacter>())
	{
		AProjectDCharacter* Character = Cast<AProjectDCharacter>( OtherActor );
		Character->TakeDamage( AttackDamage );
	}
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

	AttackSphere->SetCollisionEnabled( ECollisionEnabled::Type::QueryAndPhysics );

	FTimerHandle Handle;

	GetWorld()->GetTimerManager().SetTimer
	(
		Handle , FTimerDelegate::CreateLambda(
			[this]()
			{
				AttackSphere->SetCollisionEnabled( ECollisionEnabled::Type::QueryAndPhysics );
			} ) ,
		0.2 , false
	);

	if(DecalComp)
		DecalComp->DestroyComponent();
}

