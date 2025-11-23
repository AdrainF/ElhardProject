// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/STT_UseGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"


USTT_UseGameplayAbility::USTT_UseGameplayAbility(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	bShouldCallTick = true;
}

void USTT_UseGameplayAbility::OnAbilityEnded(const FAbilityEndedData& Data)
{
	bAbilityFinished = true;
}

EStateTreeRunStatus USTT_UseGameplayAbility::EnterState(FStateTreeExecutionContext& Context,
                                                        const FStateTreeTransitionResult& Transition)
{
	
	 Super::EnterState(Context, Transition);

	
	if (ACharacter* AICharacter=Cast<ACharacter>(GetOwnerActor(Context)))
	{
		CachedASC=AICharacter->FindComponentByClass<UAbilitySystemComponent>();
		if (CachedASC && AbilityToActivate)
		{
			AbilityEndedHandle = CachedASC->OnAbilityEnded.AddUObject(
				this,
				&USTT_UseGameplayAbility::OnAbilityEnded
			);
			CachedASC->TryActivateAbilityByClass(AbilityToActivate);
			
			return EStateTreeRunStatus::Running;
		}
		
	}
	
	return EStateTreeRunStatus::Failed;
}

EStateTreeRunStatus USTT_UseGameplayAbility::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	//Super::Tick(Context, DeltaTime);
	if (bAbilityFinished)
	{
		if (CachedASC)
		{
			CachedASC->OnAbilityEnded.Remove(AbilityEndedHandle);
		}
		return EStateTreeRunStatus::Succeeded;
	}
	
	return EStateTreeRunStatus::Running;
}

