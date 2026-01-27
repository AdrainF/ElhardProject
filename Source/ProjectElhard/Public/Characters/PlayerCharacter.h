// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Characters/CharacterBase.h"
#include "PlayerCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;
class UCombatComponent;
class UGameplayAbility;
class UInteractionComponent;
class UItemContainerComponent;
/**
 * 
 */
UCLASS()
class PROJECTELHARD_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	APlayerCharacter();
protected:
	UPROPERTY(EditAnywhere,Category="CameraComp")
	TObjectPtr<UCameraComponent> Camera=nullptr;

	UPROPERTY(EditAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom = nullptr;
	// Combat Component
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Combat")
	UCombatComponent* CombatComp=nullptr;
	// Interaction Component
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Interaction")
	UInteractionComponent* InteractionComp=nullptr;
	//Change for InventoryComponent later
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Inventory")
	UItemContainerComponent * ItemContainerComp = nullptr;

	
	
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS|Ability Dash")
	TSubclassOf<UGameplayAbility> DashAbility = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS| Ability Primary Attack")
	TSubclassOf<UGameplayAbility> PrimaryAttack = nullptr;
	
	UFUNCTION(BlueprintCallable)
	UCombatComponent* GetCombatComponent() const { return CombatComp; }
	
};
