// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Enums/E_ItemRarity.h"
#include "Enums/E_ItemType.h"
#include "DA_ItemBase.generated.h"

/**
 * 
 */

UCLASS()
class PROJECTELHARD_API UDA_ItemBase : public UDataAsset
{
	GENERATED_BODY()

protected:
	// The name of the item
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Base Data", meta = (AllowPrivateAccess = "true"))
	FName ItemName;
	//  Maximum stack size for the item
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Base Data", meta = (AllowPrivateAccess = "true"))
	int32 MaxStackSize;
	// Icon representing the item
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Base Data", meta = (AllowPrivateAccess = "true"))
	UTexture2D* ItemIcon;
	// 3D mesh representing the item
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Base Data", meta = (AllowPrivateAccess = "true"))
	UStaticMesh* ItemMesh;
	// Rarity level of the item
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Base Data", meta = (AllowPrivateAccess = "true"))
	E_ItemRarity ItemRarity;
	// Type/category of the item
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Base Data", meta = (AllowPrivateAccess = "true"))
	E_ItemType ItemType;
	// Monetary value of the item
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Base Data", meta = (AllowPrivateAccess = "true"))
	int32 Value;
};
