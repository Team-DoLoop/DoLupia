
#pragma once

#include "CoreMinimal.h"
#include "Items/EquipItemBase.h"
#include "SwordBase.generated.h"

class UItemBase;

UCLASS()
class PROJECTD_API ASwordBase : public AEquipItemBase
{
	GENERATED_BODY()
	
public:	
	ASwordBase();

protected:
	virtual void BeginPlay() override;

};
