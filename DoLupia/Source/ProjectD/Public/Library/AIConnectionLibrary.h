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

public:

	FString SendNPCConversationToServer( FString& message );
	void SendImageKeywordToServer( const FString& keyword );
	
	void ReqMessage( const FString& url , const FString& msg );
	void ResMessage( FHttpRequestPtr Request , FHttpResponsePtr Response , bool bConnectedSuccessfully );
	void ReqAIImage( const FString& url , const FString& msg );
	void ResAIImage( FHttpRequestPtr Request , FHttpResponsePtr Response , bool bConnectedSuccessfully );

private:
	/* IP Adress, Port */
	FString LanIP = "192.168.75.246";
	FString WifiIP = "172.16.216.55";
	FString ServerPort = "8000";

	FString npc_message;
	
};
