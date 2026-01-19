// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EnemyCharacterBase.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CombatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
//#include "Weapons/EP_WeaponBase.h"

class AAIController;

AEnemyCharacterBase::AEnemyCharacterBase()
{
	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
}

void AEnemyCharacterBase::OnDeath()
{
	Super::OnDeath();

	if (AAIController* AIC = Cast<AAIController>(GetController()))
	{
		AIC->BrainComponent->StopLogic(TEXT("Death"));
	}
}
