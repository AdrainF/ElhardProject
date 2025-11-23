// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "STT_UseGameplayAbility.generated.h"

/**
 * 
 */
class UGameplayAbility;
class UAbilitySystemComponent;
UCLASS()
class PROJECTELHARD_API USTT_UseGameplayAbility : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()

public:
	USTT_UseGameplayAbility(const FObjectInitializer& ObjectInitializer);
protected:
	// Ability to activate
	UPROPERTY(EditAnywhere, Category = "ActivateAbility")
	TSubclassOf<UGameplayAbility> AbilityToActivate;
	
	UPROPERTY()
	UAbilitySystemComponent* CachedASC;

	FDelegateHandle AbilityEndedHandle;

	bool bAbilityFinished = false;

	UFUNCTION()
	void OnAbilityEnded(const FAbilityEndedData& Data);
	
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) ;
	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) ;

};
