// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Inventory/InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	InitializeEmptySlots();
}

void UInventoryComponent::InitializeEmptySlots()
{
	for (int32 i = 0; i < InventorySize; ++i)
	{
		Items.Add(FItem(nullptr, 0));
	}
}
