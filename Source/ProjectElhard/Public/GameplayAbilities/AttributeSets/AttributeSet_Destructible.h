// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet_Destructible.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDestruction);
/**
 * 
 */
UCLASS()
class PROJECTELHARD_API UAttributeSet_Destructible : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAttributeSet_Destructible();
	
	// Event triggered whenever Destruction occurs
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnDestruction OnDestruction;
	//Health Attribute
	UPROPERTY(BlueprintReadOnly,Category="Attributes")
	FGameplayAttributeData Health=100;
	ATTRIBUTE_ACCESSORS_BASIC(UAttributeSet_Destructible, Health);
	//MaxHealth Attribute
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxHealth=100;
	ATTRIBUTE_ACCESSORS_BASIC(UAttributeSet_Destructible, MaxHealth);

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
};
