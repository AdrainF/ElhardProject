// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Weapon/DA_WeaponBase.h"
#include "Items/ItemBase.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "WeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTELHARD_API AWeaponBase : public AItemBase
{
	GENERATED_BODY()

public:
	AWeaponBase();

	// Gameplay effect to apply when a weapon successfully hits an actor
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS")
	TSubclassOf<UGameplayEffect> GameplayEffectToApply;
	// Point at weapon where we start trace
	UPROPERTY(EditDefaultsOnly,Category="Collison")
	USceneComponent* Start_Collision;
	// Point at weapon where we end trace
	UPROPERTY(EditDefaultsOnly,Category="Collison")
	USceneComponent* End_Collision;
	// Getter for WeaponData
	UFUNCTION(BlueprintCallable)
	UDA_WeaponBase* GetWeaponData() const { return Cast<UDA_WeaponBase>(ItemDataAsset.ItemAsset); }
    // Damage value set from Ability
	UPROPERTY()
	float CurrentDamage=0.f;
protected:
	UPROPERTY()
	bool bStartWeaponTrace=false;
	// List of actors that have already been hit, to avoid multiple hits
	TArray<AActor*> HitActors;
	
public:
	UFUNCTION(BlueprintCallable)
	void WeaponTrace(ACharacter* OwnerCharacter);
	UFUNCTION(BlueprintCallable)
	bool IsStartWeaponTrace() const { return bStartWeaponTrace; }
	UFUNCTION(BlueprintCallable)
	void StartWeaponTrace(){bStartWeaponTrace = true;}
	UFUNCTION(BlueprintCallable)
	void StopWeaponTrace(FGameplayEventData Payload){bStartWeaponTrace = false; HitActors.Empty(); } 
	UFUNCTION(BlueprintCallable)
	void SetStartwWeaponTrace(bool bStart){bStartWeaponTrace = bStart;}
};
