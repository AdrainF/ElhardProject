// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilities/GA_AI_AttackBase.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Components/CombatComponent.h"
//#include "Weapons/EP_WeaponBase.h"

UGA_AI_AttackBase::UGA_AI_AttackBase()
{
}

void UGA_AI_AttackBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                        const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
		return;
	// Check Animation
	if (!AttackAnimation)
		return;
	// Cache Combat Component
	const AActor* Owner = GetOwningActorFromActorInfo();
	checkf(Owner, TEXT("GA_AI_AttackBase::ActivateAbility: Owner is null!"));
	CombatCompCached = Owner->FindComponentByClass<UCombatComponent>();
 //    
	// const AEP_WeaponBase* Weapon = CombatCompCached->GetEquippedWeapon();
	// if (!Weapon)
	// {
	// 	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	// 	return;
	// }

	// Weapon traces
	Task_StartTrace = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
		this, FGameplayTag::RequestGameplayTag("Event.WeaponTrace.Start"));
	
	Task_StartTrace->EventReceived.AddDynamic(this, &UGA_AI_AttackBase::OnWeaponTrace);
	Task_StartTrace->ReadyForActivation();

	Task_EndTrace = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
		this, FGameplayTag::RequestGameplayTag("Event.WeaponTrace.End"));
	//Task_EndTrace->EventReceived.AddDynamic(Weapon, &AEP_WeaponBase::StopWeaponTrace);
	Task_EndTrace->ReadyForActivation();

	// Rotation Event
	Task_Rotation = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
		this, FGameplayTag::RequestGameplayTag("Event.Rotation"));
	Task_Rotation->EventReceived.AddDynamic(CombatCompCached, &UCombatComponent::RotationToSoftTarget);
	Task_Rotation->ReadyForActivation();

	PlayMontage();
}

void UGA_AI_AttackBase::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	SendGameplayEvent(  FGameplayTag::RequestGameplayTag("Event.Ability.End"), FGameplayEventData());
	
}

void UGA_AI_AttackBase::PlayMontage()
{
	if (!CombatCompCached || !AttackAnimation)
		return;
	PlayMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
	   this,
	   "AIAttackMontage",
	   AttackAnimation
   );
	
	
	PlayMontageTask->OnCompleted.AddDynamic(this, &UGA_AI_AttackBase::OnMontageCompleted);
	PlayMontageTask->OnBlendOut.AddDynamic(this, &UGA_AI_AttackBase::OnMontageBlendOut);

	PlayMontageTask->ReadyForActivation();
	
}

void UGA_AI_AttackBase::OnMontageCompleted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}

void UGA_AI_AttackBase::OnMontageBlendOut()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);

}

void UGA_AI_AttackBase::OnWeaponTrace(FGameplayEventData Payload)
{
	// if (AEP_WeaponBase* Weapon = CombatCompCached->GetEquippedWeapon())
	// {
	// 	Weapon->StartWeaponTrace();
	// 	Weapon->CurrentDamage = CurrentAttackDamage; // tu ustawiasz dmg
	// }
}


