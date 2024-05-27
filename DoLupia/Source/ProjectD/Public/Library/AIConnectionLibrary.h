// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AIConnectionLibrary.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnWebApiResponseReceived , FString , Response );

UCLASS()
class PROJECTD_API UAIConnectionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

/**
	2024.05.14 함수 호출할 때 , string으로 매개변수 선언되어 있음. 
	2024.05.16 매개변수 int 로 변경 완료
	2024.05.22 Library 싱글톤 패턴 적용
	2024.05.26 이미지 생성 요청 Player / Boss Status Effects 분기
*/
public:
	//
	static UAIConnectionLibrary* GetInstance( UObject* WorldContextObject );

	void SendNPCConversationToServer( const FString& message );
	//void SendImageKeywordToServer( const FString& keyword );
	void SendImageKeywordToServer( int32 keyword );
	void LoadImageToMaterial();
	FString SetupAITextureURL();

	void SendPImgToSrv( int32 keyword );
	void SendBImgToSrv( int32 keyword );
	

	UPROPERTY( BlueprintAssignable )
	FOnWebApiResponseReceived OnWebApiResponseReceived;

	UPROPERTY( BlueprintReadOnly )
	FString LastWebResponse;


private:
	void ReqMessage( const FString& url , const FString& msg );
	void ResMessage( FHttpRequestPtr Request , FHttpResponsePtr Response , bool bConnectedSuccessfully );
	void ReqAIImage( const FString& url , const FString& msg);
	void ResAIImage( FHttpRequestPtr Request , FHttpResponsePtr Response , bool bConnectedSuccessfully );

	/* IP Adress, Port */
	static FString LanIP ;
	static FString WifiIP ;
	static FString ServerPort ;

	static UAIConnectionLibrary* Instance;
	UObject* WorldContext;
	void Initialize( UObject* WorldContextObject );
	
};
