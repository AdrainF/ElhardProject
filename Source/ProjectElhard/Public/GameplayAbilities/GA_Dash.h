// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Dash.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTELHARD_API UGA_Dash : public UGameplayAbility
{
	GENERATED_BODY()
protected:
	// Curve used to modify the strength over time for the dash ability
	// This allows for variation in dash speed or force over its duration
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dash")
	TObjectPtr<UCurveFloat> StrengthOverTime;

	// The length of the dash (distance in Unreal units)
	// This is how far the player will travel during the dash
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dash")
	float DashLenght = 100.0f;

	// The duration of the dash ability
	// This is the time it takes to complete the dash
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dash")
	float Duration = 1.0f;

	// Function that is called to stop the ability
	// This will be triggered manually or when the dash is finished
	UFUNCTION()
	void StopAbility();

	// Overridden function to activate the ability
	// This is called when the ability is triggered (e.g., player presses a button to dash)
	// The function handles what happens when the dash ability is activated
	void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	// Overridden function to end the ability
	// This is called when the ability is finished or cancelled (e.g., dash ends)
	// Handles cleanup and stopping the ability
	void EndAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility,
		bool bWasCancelled) override;
};
