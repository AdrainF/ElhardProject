// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilities/AttributeSets/EP_BasicAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Characters/CharacterBase.h"

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
		UE_LOG(LogTemp, Log, TEXT("Health changed: %f (Delta: %f)"), NewHealth, Delta);
	}
}

void UEP_BasicAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		// Clamp Health between 0 and MaxHealth
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	else if (Attribute == GetStaminaAttribute())
	{
		// Clamp Stamina between 0 and MaxStamina
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxStamina());
	}
}

void UEP_BasicAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (NewValue <= 0.f && Attribute == GetHealthAttribute())
	{
		// Trigger OnDeath event
		//OnDeath.Broadcast();
		ACharacterBase * OwningCharacter = Cast<ACharacterBase>(GetOwningActor());
		if (OwningCharacter)
		{
			OwningCharacter->OnDeath();
		}
	}
	
}
