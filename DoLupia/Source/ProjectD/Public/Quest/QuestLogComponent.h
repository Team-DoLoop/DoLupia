#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestLogComponent.generated.h"

class AQuest_Base;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FQuestDataLoadedSignature , FName , QuestID );

UCLASS( ClassGroup = (Custom) , meta = (BlueprintSpawnableComponent) )
class PROJECTD_API UQuestLogComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UQuestLogComponent();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction ) override;

    UPROPERTY( BlueprintAssignable )
    FQuestDataLoadedSignature OnQuestDataLoaded;

public:
    UPROPERTY()
    TArray<FName> CurrentActiveQuests;

    UPROPERTY()
    TArray<FName> CompletedQuests;

    UPROPERTY()
    FName CurrentTrackedQuest;

    UPROPERTY()
    TArray<AQuest_Base*> CurrentQuest; // 수정: AQuest_Base* 에서 UQuest_Base* 로 변경

    UFUNCTION()
    void AddNewQuest( FName QuestID );

    UFUNCTION()
    bool QueryActiveQuest( FName QuestID );
};

