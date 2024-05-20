// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/AIConnectionLibrary.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "ImageUtils.h"
#include "Engine.h"
#include "AI/AIMarterialTestActor.h"
#include "Library/JsonLibrary.h"


void UAIConnectionLibrary::SendNPCConversationToServer( const FString& message )
{
	TMap<FString , FString> msgData;
	FString msg = message;
	msgData.Add( TEXT( "message" ) , msg );

	FString sendJson = UJsonLibrary::MapToJsonStr( msgData );

	/* AI Server Connection */
	FString ServerURL = "http://" + LanIP + ":" + ServerPort + "/chat";
	ReqMessage( ServerURL , sendJson );
}

void UAIConnectionLibrary::SendImageKeywordToServer( int32 keyword )
{
	//TMap<FString , FString> imgData;
	//FString ImgKeyword = keyword;

	TMap<FString , int32> imgData;
	int32 ImgKeyword = keyword;

	imgData.Add( TEXT( "Img_keywords" ) , ImgKeyword );

	FString sendJson = UJsonLibrary::MapToJsonInt( imgData );

	/* AI Server Image Request */
	FString ServerURL = "http://" + LanIP + ":" + ServerPort + "/imageAI";
	ReqAIImage( ServerURL , sendJson );


}

void UAIConnectionLibrary::LoadImageToMaterial()
{
	for (TActorIterator<AAIMarterialTestActor> ActorItr( GetWorld() ); ActorItr; ++ActorItr)
	{
		UE_LOG( LogTemp , Warning , TEXT( "UAITestWidget::ChangeMaterial - Searching Actors..." ) );
		// Call the function on the actor
		ActorItr->LoadWebImage();

	}
}

void UAIConnectionLibrary::ReqMessage(const FString& url, const FString& msg)
{
	auto& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();
	req->SetURL( url );
	req->SetVerb( TEXT( "POST" ) );
	req->SetHeader( TEXT( "Content-Type" ) , TEXT( "application/json" ) );
	req->SetContentAsString( msg );

	req->OnProcessRequestComplete().BindUObject( this, &UAIConnectionLibrary::ResMessage );
	req->ProcessRequest();
}

void UAIConnectionLibrary::ResMessage(FHttpRequestPtr Request, FHttpResponsePtr Response,
	bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		UE_LOG( LogTemp , Warning , TEXT( "Response Success... %d" ) , Response->GetResponseCode() );
		
		FString result = Response->GetContentAsString();
		UE_LOG( LogTemp , Warning , TEXT( "result : [%s]" ) , *result )

		//나중에 여기서 받은 문자열을 NPC 혹은 gamemode 에 보내는 로직 필요
	}
	else
	{
		if (Request->GetStatus() == EHttpRequestStatus::Succeeded)
		{
			UE_LOG( LogTemp , Warning , TEXT( "Response Failed... %d" ) , Response->GetResponseCode() );
		}
	}

}


void UAIConnectionLibrary::ReqAIImage(const FString& url, const FString& msg)
{
	auto& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();
	req->SetURL( url );
	req->SetVerb( TEXT( "POST" ) );
	req->SetHeader( TEXT( "Content-Type" ) , TEXT( "application/json" ) );
	req->SetContentAsString( msg );
	req->OnProcessRequestComplete().BindUObject( this , &UAIConnectionLibrary::ResAIImage );
	req->ProcessRequest();
}

void UAIConnectionLibrary::ResAIImage(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		UE_LOG( LogTemp , Warning , TEXT( "Response Success... %d" ) , Response->GetResponseCode() );

		// 이미지 저장 로직 저장 X -> 서버에서 생성된 이미지를 띄우는 형식으로 변경
		/*
		TArray<uint8> buf = Response->GetContent();
		FString imgPath = FPaths::ProjectContentDir() + "/AI/Texture/AITexture.png";
		FFileHelper::SaveArrayToFile( buf , *imgPath );
		*/
	}
	else
	{
		if (Request->GetStatus() == EHttpRequestStatus::Succeeded)
		{
			UE_LOG( LogTemp , Warning , TEXT( "Response Failed... %d" ) , Response->GetResponseCode() );
		}
	}
}
