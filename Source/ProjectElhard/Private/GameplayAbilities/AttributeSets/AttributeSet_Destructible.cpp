// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilities/AttributeSets/AttributeSet_Destructible.h"

#include "GameplayEffectExtension.h"

UAttributeSet_Destructible::UAttributeSet_Destructible()
{
}

void UAttributeSet_Destructible::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
		
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		float NewHealth = GetHealth();
		float Delta = Data.EvaluatedData.Magnitude; // The amount added or removed
		//OnHealthChange.Broadcast(nullptr, this, NewHealth, Delta); // Broadcast health change
		UE_LOG(LogTemp, Log, TEXT("Health changed: %f (Delta: %f)"), NewHealth, Delta);
	}
}

void UAttributeSet_Destructible::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if ( Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
		
		
	}
}

void UAttributeSet_Destructible::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue,
	float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	
	if (NewValue <= 0.f && Attribute == GetHealthAttribute())
	{
		// Trigger OnDestructyion event
		OnDestruction.Broadcast();
	}
}
