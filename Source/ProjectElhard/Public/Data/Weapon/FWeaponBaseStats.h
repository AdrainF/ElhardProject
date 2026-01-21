#pragma once
#include "CoreMinimal.h"
#include "FWeaponBaseStats.generated.h"

USTRUCT(BlueprintType)
struct FWeaponBaseStats
{
	GENERATED_BODY()


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float BaseDamage =0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AttackSpeed =0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CritChance =0.0f;
};
