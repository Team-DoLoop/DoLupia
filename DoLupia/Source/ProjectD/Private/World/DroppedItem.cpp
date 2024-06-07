// Fill out your copyright notice in the Description page of Project Settings.


#include "World/DroppedItem.h"

#include "Characters/ProjectDCharacter.h"
#include "Characters/Components/InventoryComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Library/BezierMovementLibrary.h"
#include "Spawner/ItemSpawner.h"

// Sets default values
ADroppedItem::ADroppedItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>( "Item StaticMesh" );
	SetRootComponent( ItemMesh );

	SphereComponent = CreateDefaultSubobject<USphereComponent>( "Item Collision" );
	SphereComponent->InitSphereRadius( 50.0f );
	SphereComponent->SetCollisionProfileName( TEXT( "OverlapAllDynamic" ) );
	SphereComponent->SetCollisionEnabled( ECollisionEnabled::NoCollision );
	SphereComponent->SetupAttachment( GetRootComponent() );



}

void ADroppedItem::SetItemStaticMesh(UStaticMesh* StaticMesh) const
{
	ItemMesh->SetStaticMesh( StaticMesh );
	SphereComponent->SetSphereRadius( FMath::Max3( ItemMesh->Bounds.BoxExtent.X , ItemMesh->Bounds.BoxExtent.Y , ItemMesh->Bounds.BoxExtent.Z ) * 2.0 );
}

// Called when the game starts or when spawned
void ADroppedItem::BeginPlay()
{
	Super::BeginPlay();

	//UBezierMovementLibrary::MoveObjectAlongCurve( this , this , GetActorLocation() , FVector(100.f,100.f,100.f) , 0.77f);
	OriRotator = ItemMesh->GetRelativeRotation();

	FVector StartPosition = GetActorLocation();
	FVector StartRotation = OriRotator.Vector();

	// 위치와 회전 값을 XOR 연산하여 고유한 시드 값 생성
	// 나중에 확률 추가하려면 따로 구현 해야함.
	uint32 Seed = StartPosition.X;
	Seed = Seed ^ (uint32)StartPosition.Y;
	Seed = Seed ^ (uint32)StartPosition.Z;
	Seed = Seed ^ (uint32)StartRotation.X;
	Seed = Seed ^ (uint32)StartRotation.Z;
	Seed = Seed ^ (uint32)StartRotation.Y;

	FRandomStream RandomStream( Seed );

	SpinRotator = FRotator
	(
		(float)RandomStream.RandRange( 1 , 10 ) * 0.3f,
		(float)RandomStream.RandRange( 1 , 10 ) * 0.3f ,
		(float)RandomStream.RandRange( 1 , 10 ) * 0.3f
	);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ADroppedItem::OnTouchesGroundBeginOverlap);
}

// Called every frame
void ADroppedItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(SphereComponent->GetCollisionEnabled() == ECollisionEnabled::NoCollision)
		PerformBoxTrace();

}

void ADroppedItem::OnTouchesGroundBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AProjectDCharacter* MyCharacter = Cast<AProjectDCharacter>(OtherActor);

	// 만약 캐릭터이고 && 캐릭터의 인벤토리가 부족하지 않다면? 
	if(MyCharacter)
	{
		// 나중에 시스템 콜 추가예정 -> 인벤토리 부족
		MyCharacter->GetInventory()->HandelAddItem(ItemReference, true);
		SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		MyItemSpawner->ReturnItem( this );
		MyItemSpawner->SetActive( this , false );
		ItemMesh->SetRelativeRotation(OriRotator);
		ItemMesh->SetSimulatePhysics( false );
	}
}

void ADroppedItem::PerformBoxTrace()
{
	const FVector& Start = GetActorLocation() + FVector(0.f, 0.f, ItemMesh->Bounds.BoxExtent.Z);
	const FVector& End = Start - FVector( 0.f , 0.f , ItemMesh->Bounds.BoxExtent.Z);
	const FVector& HalfSize = ItemMesh->Bounds.BoxExtent * 0.52f;
	const FRotator& Orientation = GetActorRotation();

	// 바닥과 충돌을 감지하기 위해 월드 스태틱 오브젝트 타입을 추가
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add( UEngineTypes::ConvertToObjectType( ECollisionChannel::ECC_WorldStatic ) ); // 월드 스태틱 오브젝트를 트레이스

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add( this ); // 자신을 무시

	FHitResult OutHit;

	if (bool bHit = UKismetSystemLibrary::BoxTraceSingleForObjects(
		this ,
		Start ,
		End ,
		HalfSize ,
		Orientation ,
		ObjectTypes ,
		false ,
		ActorsToIgnore ,
		EDrawDebugTrace::None,
		OutHit ,
		true ,
		FLinearColor::Red ,
		FLinearColor::Green,
		1.0f
	))
	{
		SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		ItemMesh->SetSimulatePhysics(true);
	}
	else
	{
		const FRotator& CurrentRotatar = ItemMesh->GetRelativeRotation();
		ItemMesh->SetRelativeRotation( FMath::RInterpTo( CurrentRotatar , CurrentRotatar + SpinRotator , GetWorld()->GetTimeSeconds() , 0.1f ) );
	}

}



