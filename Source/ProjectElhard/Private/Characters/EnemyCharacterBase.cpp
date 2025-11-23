// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EnemyCharacterBase.h"

#include "Components/CombatComponent.h"

AEnemyCharacterBase::AEnemyCharacterBase()
{
	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
}
