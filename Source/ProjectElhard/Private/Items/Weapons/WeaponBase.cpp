// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/WeaponBase.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystemBlueprintLibrary.h"

AWeaponBase::AWeaponBase()
{
	Start_Collision= CreateDefaultSubobject<USceneComponent>(TEXT("StartCollision"));
	Start_Collision->SetupAttachment(ItemMesh);
	End_Collision= CreateDefaultSubobject<USceneComponent>(TEXT("EndCollision"));
	End_Collision->SetupAttachment(ItemMesh);
}

void AWeaponBase::WeaponTrace(ACharacter* OwnerCharacter)
{
	TArray<struct FHitResult> OutHitResults;
	const FVector Start=Start_Collision->GetComponentLocation();
	const FVector End=End_Collision->GetComponentLocation();;
	// Set up collision to detect pawns
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

	const float HalfHeight = (End - Start).Size() / 2.0f;
	FCollisionShape CollisionShape;
	CollisionShape.SetCapsule(10.0f, HalfHeight);
	
	// Ignore the player to prevent self-collision
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(OwnerCharacter);
	
	
	const bool bBlockHit=OwnerCharacter->GetWorld()->SweepMultiByObjectType(OutHitResults,Start,End
		,FQuat::Identity,ObjectQueryParams
		,FCollisionShape::MakeSphere(5.f),Params);

	// Debug visualization of the capsule trace
	const FVector Center = (End + Start) / 2;
	const FColor CapsuleColor = bBlockHit ? FColor::Green : FColor::Red;

	DrawDebugCapsule(
		OwnerCharacter->GetWorld(),
		Center,
		HalfHeight,
		10.0f,
		FRotationMatrix::MakeFromZ(End - Start).ToQuat(),
		CapsuleColor,
		false,   // Not persistent
		1.0f,    // Duration
		0,       // Depth priority
		1.0f     // Thickness
	);
	// Apply gameplay effect to each valid hit actor
	for (const FHitResult& Hit : OutHitResults)
	{
		AActor* HitActor = Hit.GetActor();
		if (!HitActor || HitActors.Contains(HitActor)) continue;

		// Get ASC (Ability System Component) from the hit actor
		UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(HitActor);
		if (ASC && GameplayEffectToApply)
		{
			// Create gameplay effect spec
			FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
			FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(GameplayEffectToApply, 1.0f, ContextHandle);

			if (SpecHandle.IsValid())
			{
				SpecHandle.Data->SetSetByCallerMagnitude(
				FGameplayTag::RequestGameplayTag(FName("Ability.Attack.Primary")),
				CurrentDamage);
				// Apply effect to the target
				ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
				// Save the hit actor to prevent multiple hits in a single animation
				HitActors.Add(HitActor);
			}
		}
	
	}
}
