// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/AIConnectionLibrary.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "ImageUtils.h"
#include "Library/JsonLibrary.h"





FString UAIConnectionLibrary::SendNPCConversationToServer(FString& message )
{
	TMap<FString , FString> msgData;
	FString msg = message;
	msgData.Add( TEXT( "message" ) , msg );

	FString sendJson = UJsonLibrary::MapToJson( msgData );

	/* AI Server Connection */
	// Server Conn URL
	FString ServerURL = "http://" + WifiIP + ":" + ServerPort + "/chat";

	// Server connect
	ReqMessage( ServerURL , sendJson );

	UE_LOG( LogTemp , Warning , TEXT( "result : [%s]" ) , *npc_message )
	return npc_message;

}

void UAIConnectionLibrary::SendImageKeywordToServer(const FString& keyword )
{
	TMap<FString , FString> imgData;
	FString ImgKeyword = keyword;
	imgData.Add( TEXT( "Img_keywords" ) , ImgKeyword );

	FString sendJson = UJsonLibrary::MapToJson( imgData );

	/* AI Server Connection */
	// Server Conn URL
	FString ServerURL = "http://" + WifiIP + ":" + ServerPort + "/imageAI";

	// server connect
	ReqAIImage( ServerURL , sendJson );
}

void UAIConnectionLibrary::ReqMessage(const FString& url, const FString& msg)
{
	// FHTTPModule 객체를 가져오고 싶다.
	auto& httpModule = FHttpModule::Get();

	// UHTTPRequest 객체를 만들고 싶다.
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

	// url 설정
	req->SetURL( url );

	// verb 설정 (post)
	req->SetVerb( TEXT( "POST" ) );

	// header 설정
	req->SetHeader( TEXT( "Content-Type" ) , TEXT( "application/json" ) );

	// 보낼 정보를 담기
	req->SetContentAsString( msg );

	// 응답함수 등록
	req->OnProcessRequestComplete().BindUObject( this, &UAIConnectionLibrary::ResMessage );

	// 요청 실행
	req->ProcessRequest();
}

void UAIConnectionLibrary::ResMessage(FHttpRequestPtr Request, FHttpResponsePtr Response,
	bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		FString result = Response->GetContentAsString();

		UE_LOG( LogTemp , Warning , TEXT( "result : [%s]" ) , *result )
		//txt_chatbot->SetText( FText::FromString( result ) );
		//npc_message += FString::Printf( TEXT( "content : %s\n" ) , *result );
		npc_message = result;
	}
	else
	{
		if (Request->GetStatus() == EHttpRequestStatus::Succeeded)
		{
			UE_LOG( LogTemp , Warning , TEXT( "Responce Failed... %d" ) , Response->GetResponseCode() );
		}
	}

	//return npc_message;
}


void UAIConnectionLibrary::ReqAIImage(const FString& url, const FString& msg)
{
	// FHTTPModule 객체를 가져오고 싶다.
	auto& httpModule = FHttpModule::Get();

	// UHTTPRequest 객체를 만들고 싶다.
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

	// url 설정
	req->SetURL( url );

	// verb 설정 (post)
	req->SetVerb( TEXT( "POST" ) );

	// header 설정
	req->SetHeader( TEXT( "Content-Type" ) , TEXT( "application/json" ) );

	// 보낼 정보를 담기
	req->SetContentAsString( msg );

	// 응답함수 등록
	req->OnProcessRequestComplete().BindUObject( this , &UAIConnectionLibrary::ResAIImage );

	// 요청 실행
	req->ProcessRequest();
}

void UAIConnectionLibrary::ResAIImage(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		//바이트 배열에 응답받은 콘텐츠를 가져오고 싶다.
		TArray<uint8> buf = Response->GetContent();

		//저장한 이미지의 경로를 정하고 싶다
		FString imgPath = FPaths::ProjectContentDir() + "/AI/Texture/AITexture.png";
		UE_LOG( LogTemp , Warning , TEXT( "result : [%s]" ) , *imgPath )

		//FFileHelper의 save 함수를 통해 파일로 저장한다.
		FFileHelper::SaveArrayToFile( buf , *imgPath );

		//바이트 배열을 이미지로 변환한다.
		UTexture2D* txt = FImageUtils::ImportBufferAsTexture2D( buf );

		//그 이미지를 ui에 적용한다.
		//img_aitexture->SetBrushFromTexture( txt );

	}
	else
	{
		if (Request->GetStatus() == EHttpRequestStatus::Succeeded)
		{
			UE_LOG( LogTemp , Warning , TEXT( "Response Failed... %d" ) , Response->GetResponseCode() );
		}
	}
}
