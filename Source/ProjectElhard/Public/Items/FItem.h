#pragma once
#include "CoreMinimal.h"
#include "FItem.generated.h"

class UDA_ItemBase; 
USTRUCT(Blueprintable, BlueprintType)
struct FItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDA_ItemBase* ItemAsset=nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity=0;
	
};
