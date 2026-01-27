// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemBase.h"

#include "IDetailTreeNode.h"
#include "Components/ItemContainerComponent.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("ItemMesh"));
	ItemMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemBase::Interact_Implementation(APawn* InteractingPawn)
{
    PickUpItem(InteractingPawn);
}

void AItemBase::PickUpItem(APawn* InteractingPawn)
{
	if(!InteractingPawn) return;
	UItemContainerComponent* ItemContainer = InteractingPawn->FindComponentByClass<UItemContainerComponent>();
	if(!ItemContainer) return;
	ItemContainer->AddItem(ItemDataAsset);
	this->Destroy();
}


// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

