#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class E_WeaponType : uint8
{
	Melee        UMETA(DisplayName = "Melee"),
	Ranged       UMETA(DisplayName = "Ranged"),
	Magic        UMETA(DisplayName = "Magic"),
};
