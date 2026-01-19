// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CharacterBase.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayAbilities/AttributeSets/EP_BasicAttributeSet.h"

class AEP_WeaponBase;
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

	BasicAttributeSet->OnDeath.AddDynamic(this, &ACharacterBase::OnDeath);
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
void ACharacterBase::OnDeath()
{
	bIsDead= true;
	// Handle character death logic here (e.g., play animation, disable input, etc.)
	// 1. Deactivate movement
	GetCharacterMovement()->DisableMovement();
	GetCharacterMovement()->StopMovementImmediately();

	// 2. Deactivate capsule collision but KEEP it blocking world
	UCapsuleComponent* Capsule = GetCapsuleComponent();
	Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    
	// 3. Enable ragdoll physics on mesh
	USkeletalMeshComponent* AIMesh = GetMesh();
	AIMesh->SetCollisionProfileName(TEXT("Ragdoll"));
	AIMesh->SetSimulatePhysics(true);

	// 4. Attach mesh root to capsule location to avoid teleport dip
	AIMesh->SetAllPhysicsLinearVelocity(FVector::ZeroVector);

	//TO DO DROP WEAPON
	// Weapon->WeaponMesh->SetSimulatePhysics(true);
	// Weapon->WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	// Weapon->WeaponMesh->SetCollisionProfileName(TEXT("Ragdoll"));

	UE_LOG(LogTemp, Warning, TEXT("%s has died."), *GetName());
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

