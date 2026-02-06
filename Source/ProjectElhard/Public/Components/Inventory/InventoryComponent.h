// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Inventory/ItemContainerComponent.h"
#include "InventoryComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECTELHARD_API UInventoryComponent : public UItemContainerComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	//Slots array size
	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 InventorySize = 20;
	//Fill slots with empty items
	UFUNCTION(BlueprintCallable, Category = "Fill empty slots")
	void InitializeEmptySlots();
	
};
