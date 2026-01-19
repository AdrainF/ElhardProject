#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class E_ItemType : uint8
{
	Weapon      UMETA(DisplayName = "Weapon"),
	Armor        UMETA(DisplayName = "Armor"),
	Consumable   UMETA(DisplayName = "Consumable")
	
};