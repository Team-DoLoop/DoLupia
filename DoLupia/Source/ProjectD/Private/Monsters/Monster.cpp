// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/Monster.h"
#include "Monsters/MonsterFSM.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/SkeletalMesh.h"
// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh>MonsterMesh(TEXT("/Game/Monsters/Assets/Ancient_Golem/Mesh/SK_Ancient_Golem.SK_Ancient_Golem"));
	RootComponent->SetWorldScale3D(FVector(1.5f));
	if (MonsterMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(MonsterMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -130), FRotator(0, -90, 0));
	}

	MonsterFSM = CreateDefaultSubobject<UMonsterFSM>(TEXT("MonsterFSM"));
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonster::Damage()
{
	MonsterHP -= 10;
}

