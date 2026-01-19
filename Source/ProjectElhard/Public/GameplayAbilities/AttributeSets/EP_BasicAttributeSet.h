// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "EP_BasicAttributeSet.generated.h"

// DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(
// 	FOnHealthChange,
// 	AActor*, InstigatorActor,
// 	UEP_BasicAttributeSet*, OwningComp,
// 	float, NewHealth,
// 	float, Delta
// );
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
/**
 * 
 */
UCLASS()
class PROJECTELHARD_API UEP_BasicAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UEP_BasicAttributeSet();

	// // Event triggered whenever Health changes (damage, healing, etc)
	// UPROPERTY(BlueprintAssignable)
	// FOnHealthChange OnHealthChange;

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnDeath OnDeath;
	//Health Attribute
	UPROPERTY(BlueprintReadOnly,Category="Attributes")
	FGameplayAttributeData Health=100;
	ATTRIBUTE_ACCESSORS_BASIC(UEP_BasicAttributeSet, Health);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxHealth=100;
	ATTRIBUTE_ACCESSORS_BASIC(UEP_BasicAttributeSet, MaxHealth);

	//Stamina Attribute
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Stamina=100;
	ATTRIBUTE_ACCESSORS_BASIC(UEP_BasicAttributeSet, Stamina);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxStamina=100;
	ATTRIBUTE_ACCESSORS_BASIC(UEP_BasicAttributeSet, MaxStamina)

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
};