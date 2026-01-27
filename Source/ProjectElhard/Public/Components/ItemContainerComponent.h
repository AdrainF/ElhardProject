// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/ItemBase.h"
#include "ItemContainerComponent.generated.h"


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
	TArray<UDA_ItemBase*> Items;
	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Getter for Items
	UFUNCTION(BlueprintCallable)
	TArray<UDA_ItemBase*> GetItems();
	// Adds a new item to the container
	UFUNCTION(BlueprintCallable)
	void AddItem(UDA_ItemBase* NewItem);
	// Swaps two items in the container by their indices
	UFUNCTION(Blueprintable)
	void SwapItems(int32 IndexA, int32 IndexB);
	// Removes an item from the container by its index
	UFUNCTION(BlueprintCallable)
	void RemoveItem(int32 IndexA);
	// Finds the first empty slot in the container
	UFUNCTION(BlueprintCallable)
	void FindEmptySlot();
};
