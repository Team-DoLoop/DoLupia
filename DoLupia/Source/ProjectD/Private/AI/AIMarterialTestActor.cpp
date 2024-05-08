// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIMarterialTestActor.h"

#include "Components/BoxComponent.h"
#include "Materials/MaterialExpressionTextureSample.h"

// Sets default values
AAIMarterialTestActor::AAIMarterialTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    boxComp = CreateDefaultSubobject<UBoxComponent>( TEXT( "boxComp" ) );
    this->SetRootComponent( boxComp );

    meshComp = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "meshComp" ) );
    meshComp->SetupAttachment( RootComponent );

    meshComp->SetCollisionEnabled( ECollisionEnabled::NoCollision );

}

// Called when the game starts or when spawned
void AAIMarterialTestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIMarterialTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAIMarterialTestActor::UpdateActorMaterial()
{
    UTexture2D* LoadedTexture = LoadTextureFromImage( TEXT("D:/Projects/DoLupia/DoLupia/Content/AIImgTxt.png") );
    UMaterialInterface* LoadedMaterial = CreateMaterialFromTexture( LoadedTexture );
    if (LoadedTexture)
    {
        ApplyMaterialToMesh( meshComp , LoadedMaterial );
    }

}

void AAIMarterialTestActor::ApplyMaterialToMesh(UMeshComponent* MeshComponent, UMaterialInterface* Material)
{
	//LoadTextureFromImage()

    // 메쉬에 머티리얼 적용
    if (MeshComponent && Material)
    {
        MeshComponent->SetMaterial( 0 , Material );
    }
}

//받은 AI이미지를 텍스처로 로드
UTexture2D* AAIMarterialTestActor::LoadTextureFromImage(const FString& ImagePath)
{
    // 이미지 로드
    UTexture2D* LoadedTexture = nullptr;
    
    TArray<uint8> FileData;
    if (FFileHelper::LoadFileToArray( FileData , *ImagePath ))
    {
        // 이미지 데이터 생성
        FTexture2DMipMap* Mip = new FTexture2DMipMap();
        Mip->SizeX = 1024;  // 이미지 너비
        Mip->SizeY = 1024;  // 이미지 높이
        Mip->BulkData.Lock( LOCK_READ_WRITE );
        void* TextureData = Mip->BulkData.Realloc( FileData.Num() );
        FMemory::Memcpy( TextureData , FileData.GetData() , FileData.Num() );
        Mip->BulkData.Unlock();

        // 텍스처 생성
        LoadedTexture = UTexture2D::CreateTransient( Mip->SizeX , Mip->SizeY );
        LoadedTexture->CompressionSettings = TextureCompressionSettings::TC_Default;
        LoadedTexture->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
        LoadedTexture->SRGB = 1;
        LoadedTexture->AddToRoot();
        LoadedTexture->UpdateResource();
    }
    return LoadedTexture;
}


UMaterialInterface* AAIMarterialTestActor::CreateMaterialFromTexture(UTexture2D* Texture)
{
	UMaterialInstanceDynamic* Material = UMaterialInstanceDynamic::Create( MaterialTemplate , nullptr );
    if (Material)
    {
        Material->SetTextureParameterValue( TEXT( "TextureParam" ) , Texture );
    }
    return Material;
}




