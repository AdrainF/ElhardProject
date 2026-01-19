// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class E_ItemRarity : uint8
{
	Common      UMETA(DisplayName = "Common"),
	Rare        UMETA(DisplayName = "Rare"),
	Legendary   UMETA(DisplayName = "Legendary"),
	Set         UMETA(DisplayName = "Set")
};