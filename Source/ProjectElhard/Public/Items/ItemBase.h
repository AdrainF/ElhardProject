// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FItem.h"
#include "Core/Interfaces/InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"


UCLASS()
class PROJECTELHARD_API AItemBase : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Item Mesh")
	UStaticMeshComponent* ItemMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Item Base Data")
	FItem ItemDataAsset;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Interaction interface implementation
	void Interact_Implementation(APawn* InteractingPawn);
	
	void PickUpItem(APawn* InteractingPawn);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
