#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class E_WeaponType : uint8
{
	OneHanded        UMETA(DisplayName = "OneHanded"),
	TwoHanded      UMETA(DisplayName = "TwoHanded"),
	Wand       UMETA(DisplayName = "Wand"),
	Dagger        UMETA(DisplayName = "Dagger"),
	Staff		UMETA(DisplayName = "Staff")
};
