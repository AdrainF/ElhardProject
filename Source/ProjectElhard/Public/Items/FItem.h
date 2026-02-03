#pragma once
#include "CoreMinimal.h"
#include "FItem.generated.h"

class UDA_ItemBase; 
USTRUCT(BlueprintType)
struct FItem
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDA_ItemBase* ItemAsset=nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Quantity=0;
	
};
