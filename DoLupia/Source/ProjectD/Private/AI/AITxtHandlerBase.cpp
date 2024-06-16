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
#include "Components/TimelineComponent.h"
#include "Gamemode/PlayerGameMode.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AAITxtHandlerBase::AAITxtHandlerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>( TEXT( "RootComponent" ) );

	meshComp = CreateDefaultSubobject<USkeletalMeshComponent>( TEXT( "meshComp" ) );
	meshComp->SetupAttachment( RootComponent );

    if (!meshComp)
    {
        UE_LOG( LogTemp , Error , TEXT( "Failed to create meshComp" ) );
    }

    TimelineComp = CreateDefaultSubobject<UTimelineComponent>( TEXT( "TimelineComponent" ) );
    TimelineLength = 5.0f; // 재생 시간

    NewTexture = nullptr;
    DynamicMaterial = nullptr;

}

// Called when the game starts or when spawned
void AAITxtHandlerBase::BeginPlay()
{
	Super::BeginPlay();

    gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );
	AIlib = NewObject<UAIConnectionLibrary>();

    // Timeline 진행 중
    FOnTimelineFloat TimelineProgress;
    TimelineProgress.BindUFunction( this , FName( "UpdateDissolve" ) );
    TimelineComp->AddInterpFloat( AlphaCurve , TimelineProgress );
    TimelineComp->SetTimelineLength( TimelineLength );
    TimelineComp->SetTimelineLengthMode( ETimelineLengthMode::TL_TimelineLength );

    TimelineComp->SetLooping( false );
    TimelineComp->SetPlayRate( TimelineComp->GetTimelineLength() / TimelineLength );
    //TimelineComponent->SetPlayRate( 0.5f ); // Example setting, change as needed

    // Timeline 끝날 때
    FOnTimelineEvent TimelineFinished;
    TimelineFinished.BindUFunction( this , FName( "OnTimelineFinished" ) );
    TimelineComp->SetTimelineFinishedFunc( TimelineFinished );

    if (!meshComp )
    {
        return;
    }
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

void AAITxtHandlerBase::UpdateDissolve(float dissolve )
{
    if (DynamicMaterial)
    {
        DynamicMaterial->SetScalarParameterValue( FName( "dissolve" ) , dissolve );
    }
}

void AAITxtHandlerBase::OnTimelineFinished()
{
    if (DynamicMaterial)
    {
        DynamicMaterial->SetScalarParameterValue( FName( "dissolve" ) , 1.0f );
    }
}

void AAITxtHandlerBase::LoadWebImage()
{
    // Image Load URL Setting
    FString ServerURL = AIlib->SetupAITextureURL();

    // Image Downloading..
    UAsyncTaskDownloadImage* DownloadTask = UAsyncTaskDownloadImage::DownloadImage( ServerURL );
    if (DownloadTask)
    {
        UE_LOG( LogTemp , Warning , TEXT( "AAIMarterialTestActor::LoadWebImage - Downloading..." ) );

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

        if (!meshComp )
        {
            UE_LOG( LogTemp , Error , TEXT( "meshComp is nullptr - mesh" ) );
            return;
        }

        if (meshComp && AITxtMaterial)
        {
            DynamicMaterial = meshComp->CreateDynamicMaterialInstance( 0 , AITxtMaterial );
        }

        NewTexture = DownloadedTexture;
        if (DynamicMaterial)
        {
            DynamicMaterial->SetTextureParameterValue( FName( "A1-2345" ) , NewTexture );
            UE_LOG( LogTemp , Warning , TEXT( "AAIMarterialTestActor::OnImageDownloaded - PlayFromStart" ) );

            TimelineComp->PlayFromStart();
        }
    }
}

void AAITxtHandlerBase::OnImageDownloadFailed( UTexture2DDynamic* DownloadedTexture )
{
    UE_LOG( LogTemp , Error , TEXT( "Failed to download image" ) );
}

