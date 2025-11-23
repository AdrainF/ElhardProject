// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilities/AttributeSets/EP_BasicAttributeSet.h"
#include "GameplayEffectExtension.h"
UEP_BasicAttributeSet::UEP_BasicAttributeSet()
{
}

void UEP_BasicAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		float NewHealth = GetHealth();
		float Delta = Data.EvaluatedData.Magnitude; // The amount added or removed
		OnHealthChange.Broadcast(nullptr, this, NewHealth, Delta); // Broadcast health change
		UE_LOG(LogTemp, Log, TEXT("Health changed: %f (Delta: %f)"), NewHealth, Delta);
	}
}
