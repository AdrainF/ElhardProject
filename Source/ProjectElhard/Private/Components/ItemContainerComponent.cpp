// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ItemContainerComponent.h"

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

TArray<UDA_ItemBase*> UItemContainerComponent::GetItems()
{
	return Items;
}

void UItemContainerComponent::AddItem(UDA_ItemBase* NewItem)
{
	Items.Add(NewItem);
}

void UItemContainerComponent::SwapItems(int32 IndexA, int32 IndexB)
{
}

void UItemContainerComponent::RemoveItem(int32 IndexA)
{
}

void UItemContainerComponent::FindEmptySlot()
{
}

