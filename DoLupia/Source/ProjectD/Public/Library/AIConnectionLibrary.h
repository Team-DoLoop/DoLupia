// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AIConnectionLibrary.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnWebApiResponseReceived , FString , ResponseData );

UCLASS()
class PROJECTD_API UAIConnectionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

/**
	2024.05.14 함수 호출할 때 , string으로 매개변수 선언되어 있음. 
	2024.05.16 매개변수 int 로 변경 완료
*/
public:
	void SendNPCConversationToServer( const FString& message );
	//void SendImageKeywordToServer( const FString& keyword );
	void SendImageKeywordToServer( int32 keywords );
	void LoadImageToMaterial();

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
	FString LanIP = "192.168.75.246";
	FString WifiIP = "172.16.216.55";
	FString ServerPort = "8000";
	


};
