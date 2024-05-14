// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AIConnectionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UAIConnectionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

/**
	2024.05.14 함수 호출할 때 , string으로 매개변수 선언되어 있음. 매개변수 형식 변경해야할지 논의 필요
	2024.05.14 image to texture file 로 변환하는 함수 로직 필요
*/
public:
	void SendNPCConversationToServer( const FString& message );
	void SendImageKeywordToServer( const FString& keyword );
	
private:
	void ReqMessage( const FString& url , const FString& msg );
	void ResMessage( FHttpRequestPtr Request , FHttpResponsePtr Response , bool bConnectedSuccessfully );
	void ReqAIImage( const FString& url , const FString& msg );
	void ResAIImage( FHttpRequestPtr Request , FHttpResponsePtr Response , bool bConnectedSuccessfully );

	/* IP Adress, Port */
	FString LanIP = "192.168.75.246";
	FString WifiIP = "172.16.216.55";
	FString ServerPort = "8000";
	
};
