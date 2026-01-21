// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FWeaponBaseStats.h"
#include "GameplayTagContainer.h"
#include "Data/DA_ItemBase.h"
#include "Data/Enums/E_WeaponType.h"
#include "DA_WeaponBase.generated.h"


/**
 * 
 */
USTRUCT(BlueprintType)
struct FWeaponAttackData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 10.f;
};
UCLASS()

class PROJECTELHARD_API UDA_WeaponBase : public UDA_ItemBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data", meta = (AllowPrivateAccess = "true"))
	E_WeaponType WeaponType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Tags")
	FGameplayTagContainer WeaponTags;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data", meta = (AllowPrivateAccess = "true"))
	FWeaponBaseStats WeaponStats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data", meta = (AllowPrivateAccess = "true"))
	FName WeaponSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data", meta = (AllowPrivateAccess = "true"))
	TArray<FWeaponAttackData> AttackMontages;
};
