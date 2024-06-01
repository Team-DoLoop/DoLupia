// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AITxtHandlerBase.h"
#include "IImageWrapperModule.h"
#include "Components/BoxComponent.h"
#include "Engine/Texture2D.h"
#include "UObject/Package.h"
#include "ImageUtils.h"
#include "Materials/MaterialInstance.h"
#include "Library/AIConnectionLibrary.h"
#include "Materials/MaterialExpressionTextureSample.h"
#include "Engine/Texture2DDynamic.h" 
#include "Blueprint/AsyncTaskDownloadImage.h"
#include "Async/Async.h"
#include "TextureResource.h"


// Sets default values
AAITxtHandlerBase::AAITxtHandlerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<USkeletalMeshComponent>( TEXT( "meshComp" ) );
	meshComp->SetupAttachment( RootComponent );

}

// Called when the game starts or when spawned
void AAITxtHandlerBase::BeginPlay()
{
	Super::BeginPlay();

	AIlib = NewObject<UAIConnectionLibrary>();
}

// Called every frame
void AAITxtHandlerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAITxtHandlerBase::UpdateActorMaterial()
{
    LoadWebImage();
}

void AAITxtHandlerBase::LoadWebImage()
{
    // Image Load URL Setting
    FString ServerURL = AIlib->SetupAITextureURL();

    // Image Downloading..
    UAsyncTaskDownloadImage* DownloadTask = UAsyncTaskDownloadImage::DownloadImage( ServerURL );
    if (DownloadTask)
    {
        UE_LOG( LogTemp , Warning , TEXT( "AAIMarterialTestActor::LoadWebImage - Download" ) );
        DownloadTask->OnSuccess.AddDynamic( this , &AAITxtHandlerBase::OnImageDownloaded );
        DownloadTask->OnFail.AddDynamic( this , &AAITxtHandlerBase::OnImageDownloadFailed );
    }
}

void AAITxtHandlerBase::OnImageDownloaded( UTexture2DDynamic* DownloadedTexture )
{
    if (DownloadedTexture)
    {
        UE_LOG( LogTemp , Warning , TEXT( "AAIMarterialTestActor::OnImageDownloaded" ) );
        // 다운로드된 텍스처를 머티리얼 인스턴스에 적용
        UMaterialInstanceDynamic* DynamicMaterial = meshComp->CreateDynamicMaterialInstance( 0 , AITxtMaterial );
        // UTexture로 캐스팅
        UTexture* AITxt = Cast<UTexture>( DownloadedTexture );
        if (DynamicMaterial)
        {
            DynamicMaterial->SetTextureParameterValue( FName( "A1-2345" ) , AITxt );
        }
    }
}

void AAITxtHandlerBase::OnImageDownloadFailed( UTexture2DDynamic* DownloadedTexture )
{
    UE_LOG( LogTemp , Error , TEXT( "Failed to download image" ) );
}

