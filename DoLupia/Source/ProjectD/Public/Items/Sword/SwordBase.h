
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SwordBase.generated.h"

class UItemBase;

UCLASS(Abstract)
class PROJECTD_API ASwordBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ASwordBase();

	void ReceiveItemData(UItemBase* NewItemBase);
	virtual void Tick( float DeltaTime ) override;


protected:
	virtual void BeginPlay() override;

	

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UItemBase> ItemBase;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* SwordStaticMesh;

	// Sword의 특성이 겹치는 것들을 이 변수에 담아주세요.

};
