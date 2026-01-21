#include "GameplayAbilities/GA_PrimaryAttackCombo.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "AbilitySystemComponent.h"
#include "Components/CombatComponent.h"
#include "Items/Weapons/WeaponBase.h"


UGA_PrimaryAttackCombo::UGA_PrimaryAttackCombo()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_PrimaryAttackCombo::ActivateAbility(
    const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
    
    // Cache Combat Component
    const AActor* Owner = ActorInfo->AvatarActor.Get();
    checkf(Owner, TEXT("UGA_PrimaryAttackCombo::ActivateAbility: Owner is null!"));
    CombatCompCached = Owner->FindComponentByClass<UCombatComponent>();

    if (!CombatCompCached)
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
        return;
    }
    
    const AWeaponBase* Weapon = CombatCompCached->GetEquippedWeapon();
    if (!Weapon)
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }

    if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
        return;

    AttackMontages = Weapon->GetWeaponData()->AttackMontages;
   
    AttackIndex = 0;
    bAttackBuffered = false;
    
    // Combo Window
    Task_ComboStart = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
        this, FGameplayTag::RequestGameplayTag("Event.Combo.Start"));
    Task_ComboStart->EventReceived.AddDynamic(this, &UGA_PrimaryAttackCombo::ComboStartEventReceived);
    Task_ComboStart->ReadyForActivation();
    
    Task_ComboEnd = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
        this, FGameplayTag::RequestGameplayTag("Event.Combo.Stop"));
    Task_ComboEnd->EventReceived.AddDynamic(this, &UGA_PrimaryAttackCombo::ComboEndEventReceived);
    Task_ComboEnd->ReadyForActivation();

    // Weapon traces
    Task_StartTrace = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
        this, FGameplayTag::RequestGameplayTag("Event.WeaponTrace.Start"));
    Task_StartTrace->EventReceived.AddDynamic(this, &UGA_PrimaryAttackCombo::OnWeaponTrace);
    Task_StartTrace->ReadyForActivation();

    Task_EndTrace = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
        this, FGameplayTag::RequestGameplayTag("Event.WeaponTrace.End"));
    Task_EndTrace->EventReceived.AddDynamic(Weapon, &AWeaponBase::StopWeaponTrace);
    Task_EndTrace->ReadyForActivation();

    // Rotation Event
    Task_Rotation = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
        this, FGameplayTag::RequestGameplayTag("Event.Rotation"));
    Task_Rotation->EventReceived.AddDynamic(CombatCompCached, &UCombatComponent::RotationToSoftTarget);
    Task_Rotation->ReadyForActivation();

    // Start first attack
    PlayNextMontage();
}

void UGA_PrimaryAttackCombo::PlayNextMontage()
{
    if (!CombatCompCached || AttackMontages.Num() == 0)
        return;
    
    if (AttackIndex >= AttackMontages.Num())
    {
        AttackIndex = 0;
    }
    
    UAnimMontage* MontageToPlay = AttackMontages[AttackIndex].Montage;
    CurrentAttackDamage= AttackMontages[AttackIndex].Damage;
    if (!MontageToPlay)
        return;

    // Create animation task for this single montage
    PlayMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
        this,
        "PrimaryAttackMontage",
        MontageToPlay
    );
    CombatCompCached->SoftTargeting();
    PlayMontageTask->OnCompleted.AddDynamic(this, &UGA_PrimaryAttackCombo::OnMontageCompleted);
    PlayMontageTask->OnBlendOut.AddDynamic(this, &UGA_PrimaryAttackCombo::OnMontageBlendOut);
    // Reset buffer for this attack
    bAttackBuffered = false;

    PlayMontageTask->ReadyForActivation();
}

void UGA_PrimaryAttackCombo::ComboStartEventReceived(FGameplayEventData Payload) 
{
    if (CombatCompCached)
        CombatCompCached->bSaveAttack = false;
}

void UGA_PrimaryAttackCombo::ComboEndEventReceived(FGameplayEventData Payload)
{
    if (!CombatCompCached)
        return;
    
    if (CombatCompCached->bSaveAttack)
    {
        bAttackBuffered = true;
        
        if (PlayMontageTask)
        {
            UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
            if (ASC && ASC->IsAnimatingAbility(this))
            {
              //  ASC->CurrentMontageStop(0.3f);
                AttackIndex++;
                PlayNextMontage();
            }
        }
        
    }
    else
    {
        bAttackBuffered = false;
    }
}

void UGA_PrimaryAttackCombo::OnWeaponTrace(FGameplayEventData Payload)
{
    if (AWeaponBase* Weapon = CombatCompCached->GetEquippedWeapon())
    {
        Weapon->StartWeaponTrace();
        Weapon->CurrentDamage = CurrentAttackDamage; 
    }
}

void UGA_PrimaryAttackCombo::OnMontageCompleted()
{
    if (bAttackBuffered)
    {
        return;
    }

    AttackIndex = 0;
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}



void UGA_PrimaryAttackCombo::OnMontageBlendOut()
{
    if (!bAttackBuffered)
    {
        EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
    }
}

void UGA_PrimaryAttackCombo::EndAbility(
    const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    bool bReplicateEndAbility,
    bool bWasCancelled)
{
    END_TASK_SAFE(Task_ComboStart);
    END_TASK_SAFE(Task_ComboEnd);
    END_TASK_SAFE(Task_StartTrace);
    END_TASK_SAFE(Task_EndTrace);
    END_TASK_SAFE(Task_Rotation);
    END_TASK_SAFE(PlayMontageTask);

     AWeaponBase* Weapon = CombatCompCached->GetEquippedWeapon();
    if (Weapon)
    {
        Weapon->SetStartwWeaponTrace(false);
    }
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
