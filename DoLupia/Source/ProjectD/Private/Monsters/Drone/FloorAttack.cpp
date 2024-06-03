// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/Drone/FloorAttack.h"

#include "Characters/ProjectDCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
AFloorAttack::AFloorAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Attack Component"));
	AttackSphere->SetupAttachment(GetRootComponent());
	AttackSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	AttackSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

}

// Called when the game starts or when spawned
void AFloorAttack::BeginPlay()
{
	Super::BeginPlay();

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


// Called every frame
void AFloorAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

