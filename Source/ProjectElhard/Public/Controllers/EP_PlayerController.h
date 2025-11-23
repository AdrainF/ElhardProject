// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "EP_PlayerController.generated.h"

class UInputMappingContext;
class APlayerCharacter;
class UAbilitySystemComponent;
class UCombatComponent;

/**
 * 
 */
UCLASS()
class PROJECTELHARD_API AEP_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/** Input action for character movement */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	TObjectPtr<UInputAction> ActionMove = nullptr;

	/** Input action for looking around */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	TObjectPtr<UInputAction> ActionLook = nullptr;

	/** Input action for looking around */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Attack")
	TObjectPtr<UInputAction> ActionPrimaryAttack = nullptr;

	/** Input action for looking around */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	TObjectPtr<UInputAction> ActionDash = nullptr;
	
	/** Input mapping context to use for enhanced input */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	TObjectPtr<UInputMappingContext> InputMappingContext = nullptr;

	/** Reference to the controlled player character */
	UPROPERTY()
	TObjectPtr<APlayerCharacter> PlayerCharacter = nullptr;
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystem = nullptr;
	UPROPERTY()
	TObjectPtr<UCombatComponent> CombatComponent = nullptr;

private:
	/** Reference to the enhanced input component for binding inputs */
	UPROPERTY()
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = nullptr;

protected:
	/** Handle movement input */
	void HandleMove(const FInputActionValue& InputActionValue);

	/** Handle looking input */
	void HandleLook(const FInputActionValue& InputActionValue);

	/** Handle looking input */
	void HandlePrimaryAttack(const FInputActionValue& InputActionValue);

	/** Handle looking input */
	void HandleDash(const FInputActionValue& InputActionValue);

	/** Called when this controller possesses a pawn */
	virtual void OnPossess(APawn* APawn) override;

	/** Called when this controller unpossesses a pawn */
	virtual void OnUnPossess() override;
};
