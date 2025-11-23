// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/EP_PlayerController.h"
#include "Characters/PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystemComponent.h"
#include "Components/CombatComponent.h"
void AEP_PlayerController::HandleMove(const FInputActionValue& InputActionValue) 
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	// Calculate forward and right movement directions
	const FVector Forward = ControlRot.Vector();
	const FVector Right = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	if (PlayerCharacter)
	{
		PlayerCharacter->AddMovementInput(Forward, MovementVector.Y);
		PlayerCharacter->AddMovementInput(Right, MovementVector.X);
	}
}

void AEP_PlayerController::HandleLook(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	// Add mouse/controller input to yaw and pitch
	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void AEP_PlayerController::HandlePrimaryAttack(const FInputActionValue& InputActionValue)
{
	if (AbilitySystem && CombatComponent)
	{
		if (AbilitySystem->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("Ability.Attack.Primary")))
			{
				CombatComponent->bSaveAttack = true;
			}
			else
			{
				AbilitySystem->TryActivateAbilityByClass(PlayerCharacter->PrimaryAttack);
				CombatComponent->bSaveAttack = false;
			}
	}
}

void AEP_PlayerController::HandleDash(const FInputActionValue& InputActionValue)
{
	if (AbilitySystem)
	{
		
		AbilitySystem->TryActivateAbilityByClass(PlayerCharacter->DashAbility);
	}
}

void AEP_PlayerController::OnPossess(APawn* APawn)
{
	Super::OnPossess(APawn);

	// Cache player character
	PlayerCharacter = Cast<APlayerCharacter>(APawn);
	checkf(PlayerCharacter, TEXT("AEP_PlayerController should only possess ASPlayerCharacter instances"));
	//Cache ability system
	AbilitySystem = PlayerCharacter->GetAbilitySystemComponent();
	checkf(AbilitySystem, TEXT("Cannot get AbilitySystemComponent from PlayerCharacter"));
	// Cache combat component
	CombatComponent = PlayerCharacter->GetCombatComponent();
	checkf(CombatComponent, TEXT("Cannot get CombatComponent from PlayerCharacter"));
	
	// Cache Enhanced Input Component
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComponent, TEXT("Cannot get EnhancedInputComponent"));

	// Get Enhanced Input subsystem from local player
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(InputSubsystem, TEXT("Cannot get EnhancedInputLocalPlayerSubsystem"));

	// Clear default mappings and set custom mapping
	checkf(InputMappingContext, TEXT("InputMappingContext was not specified"));
	InputSubsystem->ClearAllMappings();
	InputSubsystem->AddMappingContext(InputMappingContext, 0);

	// Bind input actions to controller functions
	if (ActionMove)
	{
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this, &AEP_PlayerController::HandleMove);
	}
	if (ActionLook)
	{
		EnhancedInputComponent->BindAction(ActionLook, ETriggerEvent::Triggered, this, &AEP_PlayerController::HandleLook);
	}
	if (ActionPrimaryAttack)
	{
		EnhancedInputComponent->BindAction(ActionPrimaryAttack, ETriggerEvent::Triggered, this, &AEP_PlayerController::HandlePrimaryAttack);
	}
	if (ActionDash)
	{
		EnhancedInputComponent->BindAction(ActionDash, ETriggerEvent::Triggered, this, &AEP_PlayerController::HandleDash);
	}
}

void AEP_PlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}
