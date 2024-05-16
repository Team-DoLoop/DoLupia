// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/MonsterSword.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AMonsterSword::AMonsterSword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SwordMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "Sword" ) );
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SK_SWORD( TEXT( "/Game/Monsters/Assets/Weapon/Swords_Group_ThinSword_Mesh.Swords_Group_ThinSword_Mesh" ) );
	if (SK_SWORD.Succeeded())
	{
		SwordMesh->SetStaticMesh( SK_SWORD.Object );
	}

	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "CollisionComponent" ) );
	SetRootComponent( CollisionComponent );
	CollisionComponent->SetGenerateOverlapEvents( true );


}

// Called when the game starts or when spawned
void AMonsterSword::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonsterSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonsterSword::OnMyCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//공격 판정
}

