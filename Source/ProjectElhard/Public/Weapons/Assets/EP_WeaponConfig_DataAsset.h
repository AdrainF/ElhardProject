// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EP_WeaponConfig_DataAsset.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	EWT_Sword   UMETA(DisplayName = "Sword"),
	EWT_Axe    UMETA(DisplayName = "Axe"),
	EWT_Staff  UMETA(DisplayName = "Staff"),
	EWT_Bow    UMETA(DisplayName = "Bow")
};

class FSocketName;
UCLASS()
class PROJECTELHARD_API UEP_WeaponConfig_DataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	EWeaponType WeaponType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	FName WeaponSocketName;
};
