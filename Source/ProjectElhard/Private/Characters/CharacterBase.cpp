// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CharacterBase.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilities/AttributeSets/EP_BasicAttributeSet.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create ability system component
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	// Create Basic Attribute Set 
	BasicAttributeSet = CreateDefaultSubobject<UEP_BasicAttributeSet>(TEXT("BasicAttributeSet"));

	// If both created, register the attribute set with the ASC so GAS knows about it
	if (AbilitySystem && BasicAttributeSet)
	{
		AbilitySystem->AddAttributeSetSubobject(BasicAttributeSet.Get());
	}
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	// Initialize ability system actor info
	if (AbilitySystem)
	{
		AbilitySystem->InitAbilityActorInfo(this, this);
	}
	
}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystem;
}


// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

