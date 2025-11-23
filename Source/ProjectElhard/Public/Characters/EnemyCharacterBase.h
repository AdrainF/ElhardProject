// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterBase.h"
#include "EnemyCharacterBase.generated.h"

/**
 * 
 */
class UCombatComponent;
UCLASS()
class PROJECTELHARD_API AEnemyCharacterBase : public ACharacterBase
{
	GENERATED_BODY()
public:
	AEnemyCharacterBase();

	UFUNCTION(BlueprintCallable)
	UCombatComponent* GetCombatComponent() const { return CombatComp; }
protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Combat")
	UCombatComponent* CombatComp=nullptr;

	


};
