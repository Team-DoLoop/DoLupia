// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AITxtBossAttack.h"
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


// Sets default values
AAITxtBossAttack::AAITxtBossAttack()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>( TEXT( "RootComponent" ) );

    meshComp1 = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "meshComp1" ) );
    meshComp1->SetupAttachment( RootComponent );

    meshComp2 = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "meshComp2" ) );
    meshComp2->SetupAttachment( RootComponent );

    meshComp3 = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "meshComp3" ) );
    meshComp3->SetupAttachment( RootComponent );

    meshComp4 = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "meshComp4" ) );
    meshComp4->SetupAttachment( RootComponent );

    if (!meshComp1 || !meshComp2 || !meshComp3 || !meshComp4)
    {
        UE_LOG( LogTemp , Error , TEXT( "Failed to create meshComps" ) );
    }

    TimelineComp = CreateDefaultSubobject<UTimelineComponent>( TEXT( "TimelineComponent" ) );
    TimelineLength = 5.0f; // 재생 시간

    NewTexture = nullptr;
    LocalTexture = nullptr;
    DynamicMaterial1 = nullptr;
    DynamicMaterial2 = nullptr;
    DynamicMaterial3 = nullptr;
    DynamicMaterial4 = nullptr;

}

// Called when the game starts or when spawned
void AAITxtBossAttack::BeginPlay()
{
    Super::BeginPlay();

    // FFileHelper 클래스를 이용하여 로그 파일 생성
    FString FilePath = FPaths::ProjectLogDir() + TEXT( "LogFileName.log" );
    FFileHelper::SaveStringToFile( L"AAITxtBossAttack::BeginPlay -> Start" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
        &IFileManager::Get() , ELogVerbosity::Log );

    AIlib = NewObject<UAIConnectionLibrary>();
    //GetWorld()->GetTimerManager().SetTimer( DownloadTimerHandle , this , &AAITxtBossAttack::OnDownloadTimeout , 5.0f , false );

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

    if (!meshComp1 || !meshComp2 || !meshComp3 || !meshComp4)
    {
        FFileHelper::SaveStringToFile( L"AAITxtBossAttack::BeginPlay -> !meshComp1 || !meshComp2 || !meshComp3 || !meshComp4" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
            &IFileManager::Get() , ELogVerbosity::Log );

        UE_LOG( LogTemp , Error , TEXT( "meshComps is nullptr in BeginPlay" ) );
        return;
    }

    FFileHelper::SaveStringToFile( L"AAITxtBossAttack::BeginPlay -> End" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
        &IFileManager::Get() , ELogVerbosity::Log );


}

// Called every frame
void AAITxtBossAttack::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );

}

void AAITxtBossAttack::UpdateActorMaterial( FString _Attacktype )
{
    LoadWebImage();
    Attacktype = _Attacktype;
}

void AAITxtBossAttack::UpdateDissolve( float dissolve )
{
    if (DynamicMaterial1)
    {
        DynamicMaterial1->SetScalarParameterValue( FName( "dissolve" ) , dissolve );
        DynamicMaterial2->SetScalarParameterValue( FName( "dissolve" ) , dissolve );
        DynamicMaterial3->SetScalarParameterValue( FName( "dissolve" ) , dissolve );
        DynamicMaterial4->SetScalarParameterValue( FName( "dissolve" ) , dissolve );
    }
}

void AAITxtBossAttack::OnTimelineFinished()
{
    if (DynamicMaterial1)
    {
        DynamicMaterial1->SetScalarParameterValue( FName( "dissolve" ) , 1.0f );
        DynamicMaterial2->SetScalarParameterValue( FName( "dissolve" ) , 1.0f );
        DynamicMaterial3->SetScalarParameterValue( FName( "dissolve" ) , 1.0f );
        DynamicMaterial4->SetScalarParameterValue( FName( "dissolve" ) , 1.0f );
    }
}

void AAITxtBossAttack::LoadWebImage()
{
    // Image Load URL Setting
    FString ServerURL = AIlib->SetupAITextureURL();

    // Image Downloading..
    UAsyncTaskDownloadImage* DownloadTask = UAsyncTaskDownloadImage::DownloadImage( ServerURL );
    if (DownloadTask)
    {
        UE_LOG( LogTemp , Warning , TEXT( "AAIMarterialTestActor::LoadWebImage - Download" ) );
        DownloadTask->OnSuccess.AddDynamic( this , &AAITxtBossAttack::OnImageDownloaded );
        DownloadTask->OnFail.AddDynamic( this , &AAITxtBossAttack::OnImageDownloadFailed );
    }
    else
    {
        OnImageDownloadFailed( nullptr );
    }
}

void AAITxtBossAttack::OnImageDownloaded( UTexture2DDynamic* DownloadedTexture )
{
    //GetWorld()->GetTimerManager().ClearTimer( DownloadTimerHandle );

    if (DownloadedTexture)
    {
        UE_LOG( LogTemp , Warning , TEXT( "AAIMarterialTestActor::OnImageDownloaded" ) );
        // 다운로드된 텍스처를 머티리얼 인스턴스에 적용

        if (!meshComp1 || !meshComp2 || !meshComp3 || !meshComp4)
        {
            UE_LOG( LogTemp , Error , TEXT( "meshComp is nullptr - mesh" ) );
            return;
        }

        if (meshComp1 && meshComp2 && meshComp3 && meshComp4 && AITxtMaterial)
        {
            DynamicMaterial1 = meshComp1->CreateDynamicMaterialInstance( 0 , AITxtMaterial );
            DynamicMaterial2 = meshComp2->CreateDynamicMaterialInstance( 0 , AITxtMaterial );
            DynamicMaterial3 = meshComp3->CreateDynamicMaterialInstance( 0 , AITxtMaterial );
            DynamicMaterial4 = meshComp4->CreateDynamicMaterialInstance( 0 , AITxtMaterial );
        }

        NewTexture = DownloadedTexture;
        if (DynamicMaterial1 && DynamicMaterial2 && DynamicMaterial3 && DynamicMaterial4)
        {
            DynamicMaterial1->SetTextureParameterValue( FName( "A1-2345" ) , NewTexture );
            DynamicMaterial2->SetTextureParameterValue( FName( "A1-2345" ) , NewTexture );
            DynamicMaterial3 ->SetTextureParameterValue( FName( "A1-2345" ) , NewTexture );
            DynamicMaterial4->SetTextureParameterValue( FName( "A1-2345" ) , NewTexture );
            
            TimelineComp->PlayFromStart();
        }
    }
}

void AAITxtBossAttack::OnImageDownloadFailed( UTexture2DDynamic* DownloadedTexture )
{
    UE_LOG( LogTemp , Log , TEXT( "Failed to download image" ) );

    //GetWorld()->GetTimerManager().ClearTimer( DownloadTimerHandle );

    if (!meshComp1 && !meshComp2 && !meshComp3 && !meshComp4)
    {
        UE_LOG( LogTemp , Error , TEXT( "meshComp is nullptr - mesh" ) );
        return;
    }

    if (meshComp1 && meshComp2 && meshComp3 && meshComp4 && TxtMaterial)
    {
        DynamicMaterial1 = meshComp1->CreateDynamicMaterialInstance( 0 , TxtMaterial );
        DynamicMaterial2 = meshComp2->CreateDynamicMaterialInstance( 0 , TxtMaterial );
        DynamicMaterial3 = meshComp3->CreateDynamicMaterialInstance( 0 , TxtMaterial );
        DynamicMaterial4 = meshComp4->CreateDynamicMaterialInstance( 0 , TxtMaterial );
    }

    // AI 서버 연동 안되어 있을 때, 랜덤으로 텍스처 가져와서 적용
    int32 RandomIndex = FMath::RandRange( 0 , 9 );

    FString BaseFirePath = "/Game/AI/Texture/T_Boss10";
    FString BaseElecPath = "/Game/AI/Texture/T_Boss20";
    FString TextureName;
    FString FullPath;

    if ( Attacktype == "Fire" )
    {
        TextureName = FString::Printf( TEXT( "%d.T_Boss10%d" ) , RandomIndex + 1 , RandomIndex + 1 );
        FullPath = BaseFirePath + TextureName;
        LocalTexture = LoadObject<UTexture>( nullptr , *FullPath );
    }
    else if (Attacktype == "Electric")
    {
        TextureName = FString::Printf( TEXT( "%d.T_Boss20%d" ) , RandomIndex + 1 , RandomIndex + 1 );
        FullPath = BaseElecPath + TextureName;
        LocalTexture = LoadObject<UTexture>( nullptr , *FullPath );
    }

    if (DynamicMaterial1 && DynamicMaterial2 && DynamicMaterial3 && DynamicMaterial4)
    {
        DynamicMaterial1->SetTextureParameterValue( FName( "A3-4567" ) , LocalTexture );
        DynamicMaterial2->SetTextureParameterValue( FName( "A3-4567" ) , LocalTexture );
        DynamicMaterial3->SetTextureParameterValue( FName( "A3-4567" ) , LocalTexture );
        DynamicMaterial4->SetTextureParameterValue( FName( "A3-4567" ) , LocalTexture );
        UE_LOG( LogTemp , Warning , TEXT( "AAIMarterialTestActor::OnImageFailDownloaded" ) );

        TimelineComp->PlayFromStart();
    }
}


