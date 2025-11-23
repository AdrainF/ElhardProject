// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_AI_AttackBase.generated.h"

/**
 * 
 */
class UAbilityTask_PlayMontageAndWait;
class UAbilityTask_WaitGameplayEvent;
class UCombatComponent;
class UAnimMontage;
UCLASS()
class PROJECTELHARD_API UGA_AI_AttackBase : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UGA_AI_AttackBase();

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility,
		bool bWasCancelled) override;

protected:
	// Starts/continues the combo
	void PlayMontage();

	// Called when montage ends naturally
	UFUNCTION()
	void OnMontageCompleted();
    

	// Called when montage is Blend Out
	UFUNCTION()
	void OnMontageBlendOut();
	/** Cached combat component */
	UPROPERTY()
	UCombatComponent* CombatCompCached;

	/** Attack montages loaded from weapon */
	UPROPERTY(EditDefaultsOnly, Category = "GAS|Ability AI Attack")
	TObjectPtr<UAnimMontage> AttackAnimation;
	
	/** Montage task*/
	UPROPERTY()
	UAbilityTask_PlayMontageAndWait* PlayMontageTask;
	// Weapon traces
	UPROPERTY()
	UAbilityTask_WaitGameplayEvent* Task_StartTrace;

	UPROPERTY()
	UAbilityTask_WaitGameplayEvent* Task_EndTrace;
	// Rotation Event
	UPROPERTY()
	UAbilityTask_WaitGameplayEvent* Task_Rotation;
};
