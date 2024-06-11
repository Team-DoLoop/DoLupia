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

void ADroppedItem::SetItemStaticMesh(UStaticMesh* StaticMesh)
{
	ItemMesh->SetStaticMesh( StaticMesh );

	const FItemStatistics& Statistics = ItemReference->GetItemStatistics();

	ItemMesh->SetMassOverrideInKg( NAME_None , Statistics.MassScale );
	FVector Scale3D = Statistics.MeshScale;
	SetActorScale3D( Scale3D );

	GravityScale = Statistics.GravityScale;

	SphereComponent->SetSphereRadius( FMath::Max3( ItemMesh->Bounds.BoxExtent.X , ItemMesh->Bounds.BoxExtent.Y , ItemMesh->Bounds.BoxExtent.Z ) 
		* 2.5 / FMath::Max3( Scale3D.X, Scale3D.Y, Scale3D.Z));
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

	/*SpinRotator = FRotator
	(
		(float)RandomStream.RandRange( 1 , 10 ) * 0.3f,
		(float)RandomStream.RandRange( 1 , 10 ) * 0.3f ,
		(float)RandomStream.RandRange( 1 , 10 ) * 0.3f
	);*/

	ActorSpeed = UBezierMovementLibrary::VectorSeed( this );

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ADroppedItem::OnTouchesGroundBeginOverlap);
}

// Called every frame
void ADroppedItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(SphereComponent->GetCollisionEnabled() == ECollisionEnabled::NoCollision)
		PerformBoxTrace( DeltaTime );

}

void ADroppedItem::OnTouchesGroundBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AProjectDCharacter* MyCharacter = Cast<AProjectDCharacter>(OtherActor);

	// 만약 캐릭터이고 && 캐릭터의 인벤토리가 부족하지 않다면? 
	if(MyCharacter)
	{
		// 나중에 시스템 콜 추가예정 -> 인벤토리 부족
		FItemAddResult AddResult = MyCharacter->GetInventory()->HandelAddItem(ItemReference, true);

		switch (AddResult.OperationResult)
		{
		case EItemAddResult::IAR_NoItemAdded:
			MyCharacter->OnSystemCall( AddResult.ResultMessage );
			break;
		case EItemAddResult::IAR_PartialAmoutItemAdded:
			MyCharacter->OnSystemCall( AddResult.ResultMessage );
			break;
		default :
			SphereComponent->SetCollisionEnabled( ECollisionEnabled::NoCollision );
			MyItemSpawner->ReturnItem( this );
			MyItemSpawner->SetActive( this , false );
			ItemMesh->SetRelativeRotation( OriRotator );
			ItemMesh->SetSimulatePhysics( false );
			break;
		}

	}
}

void ADroppedItem::PerformBoxTrace( float DeltaTime )
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
		ItemMesh->SetRelativeRotation( FMath::RInterpTo( CurrentRotatar , CurrentRotatar + SpinRotator , DeltaTime , 0.1f ) );
		
		const float Gravity = 980.0f; // 중력 가속도 (cm/s²)
		const float Radians = FMath::DegreesToRadians( 45.0 );

		// 시간에 따른 x와 y 좌표 계산
		const float X = ActorSpeed.X * Time * FMath::Cos( Radians );
		const float Y = ActorSpeed.Y * Time * FMath::Sin( Radians ) - GravityScale * Gravity * Time * Time; //  
		const float Z = ActorSpeed.Z * Time * FMath::Cos( Radians );

		const FVector& NewPosition = FVector( (float)StartLocation.X + X , (float)StartLocation.Y + Z , (float)StartLocation.Z + Y );

		SetActorLocation( NewPosition );

		//MyItemSpawner->MoveItemAlongCurve( GetWorld(), this, StartLocation, Time, FVector( 0.0 , 0.0 , 0.0 ) , 0.77f );
		Time += DeltaTime;
	}

}



