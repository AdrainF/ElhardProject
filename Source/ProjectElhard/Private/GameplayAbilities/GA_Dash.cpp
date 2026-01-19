// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilities/GA_Dash.h"

#include "AbilitySystemComponent.h"
#include "../../../../../../../Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_ApplyRootMotionConstantForce.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/RootMotionSource.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/FastReferenceCollector.h"

void UGA_Dash::StopAbility()
{
	// Get the current ability's spec handle, actor info, and activation information
	const FGameplayAbilitySpecHandle Handle = GetCurrentAbilitySpecHandle();
	const FGameplayAbilityActorInfo* ActorInfo = GetCurrentActorInfo();
	FGameplayAbilityActivationInfo ActivationInfo = GetCurrentActivationInfo();

	// Parameters to control replication and cancellation
	bool bReplicateEndAbility = true;
	bool bWasCancelled = false;
	// End the ability with the provided parameters
	EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_Dash::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// Get the current velocity of the actor to determine the dash direction
	ACharacter* Character = Cast<ACharacter>(ActorInfo->OwnerActor);
	FVector DashDirection = Character->GetCharacterMovement()->GetLastInputVector();
	
	if (!DashDirection.IsNearlyZero())
	{
		DashDirection = DashDirection.GetSafeNormal();
	}
	// Retrieve the skeletal mesh component of the actor (used for particle system attachment)
	USkeletalMeshComponent* MeshComponent = ActorInfo->AvatarActor->
		FindComponentByClass<USkeletalMeshComponent>();

	// If the actor's velocity is zero (e.g., standing still), use the actor's forward vector for the dash direction
	if (DashDirection == FVector(0, 0, 0))
	{
		DashDirection = ActorInfo->OwnerActor->GetActorForwardVector();
	}

	// If the ability is successfully committed, apply root motion to the actor for the dash effect
	if (CommitAbility(Handle, ActorInfo, ActivationInfo))
	{

		FGameplayTag DashTag = FGameplayTag::RequestGameplayTag(FName("GameplayCue.Dash"));

		FGameplayCueParameters Params;


		Params.Instigator = ActorInfo->AvatarActor;
		K2_AddGameplayCueWithParams(DashTag, Params, true);

		// Set the mode for how root motion should behave upon completion
		ERootMotionFinishVelocityMode VelocityOnFinishMode = ERootMotionFinishVelocityMode::MaintainLastRootMotionVelocity;
		// Set the velocity when root motion finishes (here it's set to zero to stop movement after the dash)
		FVector SetVelocityOnFinish = FVector(0, 0, 0);

		// Apply the root motion constant force based on the dash direction, length, duration, etc.
		UAbilityTask_ApplyRootMotionConstantForce* RootMotionTask =
			UAbilityTask_ApplyRootMotionConstantForce::ApplyRootMotionConstantForce(
				this, "None", DashDirection, DashLenght, Duration, false, StrengthOverTime, VelocityOnFinishMode,
				SetVelocityOnFinish, 0.0f, false);

		// Ready the task for activation
		RootMotionTask->ReadyForActivation();

		// If the root motion task was created successfully, bind the StopAbility function to its finish event
		if (RootMotionTask)
		{
			RootMotionTask->OnFinish.AddDynamic(this, &UGA_Dash::StopAbility);
		}
	}
	else
	{
		// If the ability commit fails, immediately end the ability
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
	}
}

void UGA_Dash::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo())
	{
		FGameplayTag DashTag = FGameplayTag::RequestGameplayTag(FName("GameplayCue.Dash"));
		FGameplayCueParameters Params;
		Params.Instigator = ActorInfo->AvatarActor;

		ASC->RemoveGameplayCue(DashTag);
	}
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

