#pragma once
#include "CoreMinimal.h"
#include "FWeaponBaseStats.generated.h"

USTRUCT(BlueprintType)
struct FWeaponBaseStats
{
	GENERATED_BODY()


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float BaseDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AttackSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CritChance;
};
