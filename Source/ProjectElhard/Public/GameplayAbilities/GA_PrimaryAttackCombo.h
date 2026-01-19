#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_PrimaryAttackCombo.generated.h"


// safe end task macro
#define END_TASK_SAFE(TaskPtr) \
do { \
if ((TaskPtr) != nullptr) { \
(TaskPtr)->EndTask(); \
(TaskPtr) = nullptr; \
} \
} while (0)

class UAbilityTask_PlayMontageAndWait;
class UAbilityTask_WaitGameplayEvent;
class UCombatComponent;
class UAnimMontage;
struct FWeaponAttackData;

UCLASS()
class PROJECTELHARD_API UGA_PrimaryAttackCombo : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UGA_PrimaryAttackCombo();

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
    void PlayNextMontage();

    // Called when montage ends naturally
    UFUNCTION()
    void OnMontageCompleted();
    

    // Called when montage is Blend Out
    UFUNCTION()
    void OnMontageBlendOut();

    // Combo window events from notifies
    UFUNCTION()
    void ComboStartEventReceived(FGameplayEventData Payload);

    UFUNCTION()
    void ComboEndEventReceived(FGameplayEventData Payload);

   
protected:

    /** Cached combat component */
    UPROPERTY()
    UCombatComponent* CombatCompCached;

    /** Attack montages loaded from weapon */
  //  UPROPERTY()
//    TArray<FWeaponAttackData> AttackMontages;

    /** Current attack index */
    UPROPERTY()
    int32 AttackIndex = 0;

    UPROPERTY()
    float CurrentAttackDamage=0.f;
    UFUNCTION(BlueprintCallable)
    void OnWeaponTrace(FGameplayEventData Payload);

    /** Should next attack continue combo? */
    bool bAttackBuffered = false;

    /** Montage task*/
    UPROPERTY()
    UAbilityTask_PlayMontageAndWait* PlayMontageTask;

    /** Event tasks*/
    UPROPERTY()
    UAbilityTask_WaitGameplayEvent* Task_ComboStart;

    UPROPERTY()
    UAbilityTask_WaitGameplayEvent* Task_ComboEnd;

    UPROPERTY()
    UAbilityTask_WaitGameplayEvent* Task_StartTrace;

    UPROPERTY()
    UAbilityTask_WaitGameplayEvent* Task_EndTrace;

    UPROPERTY()
    UAbilityTask_WaitGameplayEvent* Task_Rotation;
};
