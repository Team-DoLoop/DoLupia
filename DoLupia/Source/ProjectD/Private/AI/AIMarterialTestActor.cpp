// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIMarterialTestActor.h"
#include "IImageWrapperModule.h"
#include "Components/BoxComponent.h"
#include "Engine/Texture2D.h"
#include "ImageUtils.h"
#include "Materials/MaterialExpressionTextureSample.h"
#include "TextureResource.h"

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
    UE_LOG( LogTemp , Warning , TEXT( "AAIMarterialTestActor::UpdateActorMaterial" ) );
    //UTexture2D* LoadedTexture = LoadTextureFromImage( TEXT("D:/Projects/DoLupia/DoLupia/Content/a.png") );
    FString imgPath = FPaths::ProjectContentDir() + "/AI/Texture/AIImgTxt.png";
    UTexture2D* LoadedTexture = LoadTextureFromImage( imgPath );
    UMaterialInterface* LoadedMaterial = CreateMaterialFromTexture( LoadedTexture );
    if (LoadedMaterial)
    {
        ApplyMaterialToMesh( meshComp , LoadedMaterial );
    }

}

void AAIMarterialTestActor::ApplyMaterialToMesh(UMeshComponent* MeshComponent, UMaterialInterface* Material)
{
    UE_LOG( LogTemp , Warning , TEXT( "AAIMarterialTestActor::ApplyMaterialToMesh" ) );

    // 메쉬에 머티리얼 적용
    if (MeshComponent && Material)
    {
        UE_LOG( LogTemp , Warning , TEXT( "AAIMarterialTestActor::ApplyMaterialToMesh - Success" ) );
        MeshComponent->SetMaterial( 0 , Material );
    }
}

//받은 AI이미지를 텍스처로 로드
UTexture2D* AAIMarterialTestActor::LoadTextureFromImage(const FString& ImagePath)
{
    UE_LOG( LogTemp , Warning , TEXT( "AAIMarterialTestActor::LoadTextureFromImage" ) );
    TArray<uint8> FileData;
    if (!FFileHelper::LoadFileToArray( FileData , *ImagePath ))
    {
        UE_LOG( LogTemp , Error , TEXT( "Failed to load image file: %s" ) , *ImagePath );
        return nullptr;
    }

    // 이미지를 PNG 형식으로 디코딩합니다.
    IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>( FName( "ImageWrapper" ) );
    TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper( EImageFormat::PNG );
    if (!ImageWrapper.IsValid() || !ImageWrapper->SetCompressed( FileData.GetData() , FileData.Num() ))
    {
        UE_LOG( LogTemp , Error , TEXT( "Failed to decode PNG image: %s" ) , *ImagePath );
        return nullptr;
    }

    // 이미지 정보를 가져옵니다.
    TArray<uint8> RawData ;

    if (!ImageWrapper->GetRaw( ERGBFormat::RGBA , 8 , RawData ))
    {
        UE_LOG( LogTemp , Error , TEXT( "Failed to retrieve image data from PNG: %s" ) , *ImagePath );
        return nullptr;
    }

    // 텍스처를 생성합니다.
    UTexture2D* Texture = UTexture2D::CreateTransient( ImageWrapper->GetWidth() , ImageWrapper->GetHeight() , PF_R8G8B8A8 );
    if (!Texture)
    {
        UE_LOG( LogTemp , Error , TEXT( "Failed to create texture." ) );
        return nullptr;
    }

    // 텍스처에 이미지 데이터를 씁니다.
    FUpdateTextureRegion2D UpdateRegion;
    UpdateRegion.SrcX = 0;
    UpdateRegion.SrcY = 0;
    UpdateRegion.DestX = 0;
    UpdateRegion.DestY = 0;
    UpdateRegion.Width = ImageWrapper->GetWidth();
    UpdateRegion.Height = ImageWrapper->GetHeight();

    // 텍스처에 업데이트할 픽셀 데이터를 설정합니다.
    Texture->UpdateTextureRegions( 0 , 1 , &UpdateRegion , ImageWrapper->GetWidth() * 4 , 4 , RawData.GetData() );

    return Texture;
}


UMaterialInterface* AAIMarterialTestActor::CreateMaterialFromTexture(UTexture2D* Texture)
{
    UE_LOG( LogTemp , Warning , TEXT( "AAIMarterialTestActor::CreateMaterialFromTexture" ) );
	UMaterialInstanceDynamic* Material = UMaterialInstanceDynamic::Create( MaterialTemplate , nullptr );
    if (Material)
    {
        UE_LOG( LogTemp , Warning , TEXT( "AAIMarterialTestActor::CreateMaterialFromTexture - Material Create" ) );
        //Material->SetTextureParameterValue( TEXT( "Texture" ) , Texture );
        UE_LOG( LogTemp , Warning , TEXT( "AAIMarterialTestActor::CreateMaterialFromTexture - Material Setup" ) );
    }
    return Material;
}




