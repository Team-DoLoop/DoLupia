// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIMarterialTestActor.h"
#include "IImageWrapperModule.h"
#include "Components/BoxComponent.h"
#include "Engine/Texture2D.h"
#include "UObject/Package.h"
#include "ImageUtils.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialExpressionTextureSample.h"
#include "Engine/Texture2DDynamic.h" 
#include "Blueprint/AsyncTaskDownloadImage.h"
#include "Async/Async.h"
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

    boxComp->SetCollisionEnabled( ECollisionEnabled::PhysicsOnly );
    meshComp->SetCollisionEnabled( ECollisionEnabled::PhysicsOnly );

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

    FString imgPath = FPaths::ProjectContentDir() + "/AI/Texture/AITexture.png";
    UTexture2D* LoadedTexture = LoadTextureFromImage( imgPath );

    // Create a new package
    /*
    UPackage* Package = CreatePackage( "MyPackage" );

    // Cook the package and save it to a file
    FString AssetPath = "Path/To/Your/Texture.uasset";
    Package->Cook( FString( "Path/To/Your/Texture.uasset" ) , true );
    */

    UE_LOG( LogTemp , Warning , TEXT( "Texture Details:" ) );
    UE_LOG( LogTemp , Warning , TEXT( "  Width: %f" ) , LoadedTexture->GetSurfaceWidth() );
    UE_LOG( LogTemp , Warning , TEXT( "  Height: %f" ) , LoadedTexture->GetSurfaceHeight() );
    UE_LOG( LogTemp , Warning , TEXT( "  Format: %p" ) , LoadedTexture->GetPlatformData() );
    

    UMaterialInterface* LoadedMaterial = CreateMaterialFromTexture( LoadedTexture );
    if (LoadedMaterial)
    {
        //ApplyMaterialToMesh( meshComp , LoadedMaterial );
        LoadWebImage();
    }

}

void AAIMarterialTestActor::LoadWebImage()
{
    UE_LOG( LogTemp , Warning , TEXT( "AAIMarterialTestActor::LoadWebImage - Call" ) );
    
    // URL을 통해 이미지를 다운로드
    FString testURL = "http://172.16.216.55:8000/ShowAITexture";
    UAsyncTaskDownloadImage* DownloadTask = UAsyncTaskDownloadImage::DownloadImage( testURL );
    if (DownloadTask)
    {
        UE_LOG( LogTemp , Warning , TEXT( "AAIMarterialTestActor::LoadWebImage - Down" ) );
        DownloadTask->OnSuccess.AddDynamic( this , &AAIMarterialTestActor::OnImageDownloaded );
        DownloadTask->OnFail.AddDynamic( this , &AAIMarterialTestActor::OnImageDownloadFailed );
    }

    UMaterialInstanceDynamic* testMaterial = meshComp->CreateDynamicMaterialInstance( 0 , MaterialTemplate2 );

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

void AAIMarterialTestActor::OnImageDownloaded(UTexture2DDynamic* DownloadedTexture)
{
    if (DownloadedTexture)
    {
        UE_LOG( LogTemp , Warning , TEXT( "AAIMarterialTestActor::OnImageDownloaded" ) );  
        // 다운로드된 텍스처를 머티리얼 인스턴스에 적용
        UMaterialInstanceDynamic* DynamicMaterial = meshComp->CreateDynamicMaterialInstance( 0 , MaterialTemplate );
        // UTexture로 캐스팅
        UTexture* testTexture = Cast<UTexture>( DownloadedTexture );
        if (DynamicMaterial)
        {
            DynamicMaterial->SetTextureParameterValue( FName( "A1-2345" ) , testTexture );
        }
    }
}

void AAIMarterialTestActor::OnImageDownloadFailed(UTexture2DDynamic* DownloadedTexture)
{
    UE_LOG( LogTemp , Error , TEXT( "Failed to download image" ) );
}

// 받은 AI이미지를 텍스처로 로드
UTexture2D* AAIMarterialTestActor::LoadTextureFromImage(const FString& ImagePath)
{
    UE_LOG( LogTemp , Warning , TEXT( "AAIMarterialTestActor::LoadTextureFromImage" ) );
    TArray<uint8> FileData;
    if (!FFileHelper::LoadFileToArray( FileData , *ImagePath ))
    {
        UE_LOG( LogTemp , Error , TEXT( "Failed to load image file: %s" ) , *ImagePath );
        return nullptr;
    }

    // 이미지 디코딩
    IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>( FName( "ImageWrapper" ) );
    TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper( EImageFormat::PNG );
    if (!ImageWrapper.IsValid() || !ImageWrapper->SetCompressed( FileData.GetData() , FileData.Num() ))
    {
        UE_LOG( LogTemp , Error , TEXT( "Failed to decode PNG image: %s" ) , *ImagePath );
        return nullptr;
    }

    // 이미지 정보
    TArray<uint8> RawData ;

    if (!ImageWrapper->GetRaw( ERGBFormat::RGBA , 8 , RawData ))
    {
        UE_LOG( LogTemp , Error , TEXT( "Failed to retrieve image data from PNG: %s" ) , *ImagePath );
        return nullptr;
    }

    // 텍스처를 생성
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

    // Create a new package
    UPackage* Package = NewObject<UPackage>( this , FName( "MyPackage" ) );

    // Save the texture as a .uasset file



    return Texture;
}


UMaterialInterface* AAIMarterialTestActor::CreateMaterialFromTexture(UTexture2D* Texture)
{
    UE_LOG( LogTemp , Warning , TEXT( "AAIMarterialTestActor::CreateMaterialFromTexture" ) );

	UMaterialInstanceDynamic* Material = UMaterialInstanceDynamic::Create( MaterialTemplate , nullptr );

	FString testURL = "http://127.0.0.1:8000/ShowAITexture";
    UTexture2D* testTexture = Cast<UTexture2D>(UAsyncTaskDownloadImage::DownloadImage(testURL));


    if (Material)
    {
        UE_LOG( LogTemp , Warning , TEXT( "AAIMarterialTestActor::CreateMaterialFromTexture - Material Create" ) );
        //Material->SetTextureParameterValue( FName( "A1-2345" ) , Texture );
        Material->SetTextureParameterValue( FName( "A1-2345" ) , testTexture );
        UE_LOG( LogTemp , Warning , TEXT( "AAIMarterialTestActor::CreateMaterialFromTexture - Material Setup" ) );
    }
    return Material;
}




