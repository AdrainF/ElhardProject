// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CharacterBase.generated.h"

class UAbilitySystemComponent;
class UEP_BasicAttributeSet;

UCLASS()
class PROJECTELHARD_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:

	
	/** Base attribute set (health, mana, etc.) for this player character */
	UPROPERTY(BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = true))
	const UEP_BasicAttributeSet* BasicAttributeSet;
	/** Ability system component to manage abilities and attributes */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAbilitySystemComponent> AbilitySystem = nullptr;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	bool bIsDead = false;
	UFUNCTION(BlueprintCallable, Category = "Death")
	virtual void OnDeath();
	/** Required by IAbilitySystemInterface: returns the ability system component */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
