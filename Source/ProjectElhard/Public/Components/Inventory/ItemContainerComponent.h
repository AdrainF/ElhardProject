// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/FItem.h"
#include "ItemContainerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTELHARD_API UItemContainerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemContainerComponent();
protected:
	// Items contained in this container
	UPROPERTY(EditAnywhere, Category = "Item Container")
	TArray<FItem> Items;
	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Getter for Items
	UFUNCTION(BlueprintCallable)
	TArray<FItem>& GetItems();
	// Adds a new item to the container
	UFUNCTION(BlueprintCallable)
	void AddItem(const FItem& NewItem);
	// Swaps two items in the container by their indices
	UFUNCTION(BlueprintCallable)
	void SwapItems(int32 IndexA, int32 IndexB);
	// Removes an item from the container by its index
	UFUNCTION(BlueprintCallable)
	void RemoveItem(int32 IndexA);
	// Finds the first empty slot in the container
	UFUNCTION(BlueprintCallable)
	void FindEmptySlot(UDA_ItemBase* ItemDA, int32& OutIndex , bool& bFound);

	// Delegate to notify when the inventory is updated
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;
};
