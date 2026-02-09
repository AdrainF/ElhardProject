// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Inventory/ItemContainerComponent.h"

#include "Data/DA_ItemBase.h"

// Sets default values for this component's properties
UItemContainerComponent::UItemContainerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UItemContainerComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
}


// Called every frame
void UItemContainerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

TArray<FItem>& UItemContainerComponent::GetItems()
{
	return Items;
}

void UItemContainerComponent::AddItem( const FItem& NewItem ,  int32 index)
{
	Items[index].ItemAsset=NewItem.ItemAsset;
	Items[index].Quantity=NewItem.Quantity;
	OnInventoryUpdated.Broadcast();
}

void UItemContainerComponent::SwapItems(int32 IndexA, int32 IndexB)
{
	Items.Swap(IndexA, IndexB);
	OnInventoryUpdated.Broadcast();
}

void UItemContainerComponent::RemoveItem(int32 IndexA)
{
	if (Items.IsValidIndex(IndexA))
	{
		Items[IndexA].Quantity=0;
		Items[IndexA].ItemAsset=nullptr;
		OnInventoryUpdated.Broadcast();
	}
}

void UItemContainerComponent::FindEmptySlot(UDA_ItemBase* ItemDA, int32& OutIndex, bool& bFound)
{
	for (int32 i = 0; i < Items.Num(); ++i)
	{
		const FItem& Item = Items[i];
		
		if (Item.ItemAsset == nullptr)
		{
			OutIndex= i;
			bFound=true;
			return;
		}
	}
	bFound=false;
	OutIndex=INDEX_NONE;
}



