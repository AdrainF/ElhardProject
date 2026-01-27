// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter.h"
#include "AbilitySystemComponent.h"
#include "Components/CombatComponent.h"
#include "Components/InteractionComponent.h"
#include "Components/ItemContainerComponent.h"
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
	ItemContainerComp = CreateDefaultSubobject<UItemContainerComponent>(TEXT("ItemContainerComponent"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}
