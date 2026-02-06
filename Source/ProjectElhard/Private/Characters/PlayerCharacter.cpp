// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter.h"
#include "Components/CombatComponent.h"
#include "Components/CurrencyComponent.h"
#include "Components/InteractionComponent.h"
#include "Components/Inventory/InventoryComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

APlayerCharacter::APlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);

	// Configure character movement to face movement direction
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	
	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
	InteractionComp = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
	//Change for InventoryComponent later
	InventoryComp = CreateDefaultSubobject<UInventoryComponent>(TEXT("ItemContainerComponent"));
	CurrencyComp = CreateDefaultSubobject<UCurrencyComponent>(TEXT("CurrencyComponent"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}
