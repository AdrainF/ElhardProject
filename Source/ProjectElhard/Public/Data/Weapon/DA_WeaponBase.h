// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Data/DA_ItemBase.h"
#include "Data/Enums/E_WeaponType.h"
#include "DA_WeaponBase.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTELHARD_API UDA_WeaponBase : public UDA_ItemBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data", meta = (AllowPrivateAccess = "true"))
	E_WeaponType WeaponType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	FGameplayTagContainer WeaponTags;
};
