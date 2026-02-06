// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CurrencyComponent.h"
#include "Data/Enums/E_CurrencyType.h"

// Sets default values for this component's properties
UCurrencyComponent::UCurrencyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCurrencyComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCurrencyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCurrencyComponent::AddCurrency(E_CurrencyType Type, int32 Amount)
{
	if (Amount>= 0)
	{
		switch (Type)
		{
			case E_CurrencyType::Gold:
				Gold += Amount;
				OnCurrencyChanged.Broadcast(Type, Gold);
				break;
			case E_CurrencyType::DarkCrystal:	
				DarkCrystal += Amount;
				OnCurrencyChanged.Broadcast(Type, DarkCrystal);
				break;
		}
	}
}

bool UCurrencyComponent::SpendCurrency(E_CurrencyType Type, int32 Amount)
{
	if (Amount <= 0)
	{
		return false;
	}
	switch (Type)
	{
		case E_CurrencyType::Gold:
			if (Gold >= Amount)
			{
				Gold -= Amount;
				OnCurrencyChanged.Broadcast(Type, Gold);
				return true;
			}
			break;
		case E_CurrencyType::DarkCrystal:
			if (DarkCrystal >= Amount)
			{
				DarkCrystal -= Amount;
				OnCurrencyChanged.Broadcast(Type, DarkCrystal);
				return true;
			}
			break;
	}
	return false;
}

int32 UCurrencyComponent::GetCurrency(E_CurrencyType Type) const
{
	switch (Type)
	{
	case E_CurrencyType::Gold:
			return Gold;
		case E_CurrencyType::DarkCrystal:
			return DarkCrystal;
		default:
			return 0;
	}
}

bool UCurrencyComponent::CanAfford(E_CurrencyType Type, int32 Amount) const
{
	if (Amount>=0)
	{
		switch (Type)
		{
		case E_CurrencyType::Gold:
			if (Gold >= Amount)
			{
				return true;
			}
			break;
		case E_CurrencyType::DarkCrystal:
			if (DarkCrystal >= Amount)
			{
				return true;
			}
			break;
		}
	}
	return false;	
}

