// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CurrencyComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCurrencyChanged, E_CurrencyType, CurrencyType, int32, NewValue);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTELHARD_API UCurrencyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCurrencyComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Currency")
	int32 Gold = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Currency")
	int32 DarkCrystal = 0;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void AddCurrency(E_CurrencyType Type, int32 Amount);

	UPROPERTY(BlueprintAssignable)
	FOnCurrencyChanged OnCurrencyChanged;

	UFUNCTION(BlueprintCallable)
	bool SpendCurrency(E_CurrencyType Type, int32 Amount);

	UFUNCTION(BlueprintCallable)
	int32 GetCurrency(E_CurrencyType Type) const;

	UFUNCTION(BlueprintCallable)
	bool CanAfford(E_CurrencyType Type, int32 Amount) const;
};
