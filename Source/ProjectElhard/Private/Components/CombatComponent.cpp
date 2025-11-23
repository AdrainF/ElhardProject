// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CombatComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Weapons/EP_WeaponBase.h"
#include "Weapons/Assets/EP_WeaponConfig_DataAsset.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UCombatComponent::HandleRotationProgress(float Value) 
{
	FRotator NewRotation = FMath::Lerp(StartRotation, TargetRotation, Value);
	NewRotation.Pitch = StartRotation.Pitch;

	if (CachedOwnerCharacter)
	{
		CachedOwnerCharacter->SetActorRotation(NewRotation);
	}
}
// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	CachedOwnerCharacter = Cast<ACharacter>(GetOwner());
	if (RotationCurve)
	{
		// Setup timeline
		FOnTimelineFloat ProgressFunction;
		ProgressFunction.BindUFunction(this, FName("HandleRotationProgress"));
		RotationTimeline.AddInterpFloat(RotationCurve, ProgressFunction);
	}
}

void UCombatComponent::EquipWeapon(AEP_WeaponBase* Weapon)
{
	if (!Weapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("EquipWeapon called with null weapon!"));
		return;
	}
	EquippedWeapon=Weapon;
	
	if (CachedOwnerCharacter)
	{
		if (USkeletalMeshComponent* CharacterMesh=CachedOwnerCharacter->GetMesh())
		{
			if (Weapon->WeaponConfig){
				const FName WeaponSocketName=Weapon->WeaponConfig->WeaponSocketName;
				Weapon->AttachToComponent(CharacterMesh,FAttachmentTransformRules::SnapToTargetNotIncludingScale,WeaponSocketName);
			}
		}
	}
}
// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//Rotation
	RotationTimeline.TickTimeline(DeltaTime);
	// Weapon Trace
	if (EquippedWeapon)
	{
		if (EquippedWeapon->IsStartWeaponTrace())
		{
			if (CachedOwnerCharacter)
			{
				EquippedWeapon->WeaponTrace(CachedOwnerCharacter);
			}
		}
	}
}

void UCombatComponent::SoftTargeting()
{
	FHitResult OutHit;
	
	// Define start and end points for the sphere trace
	const FVector Start=CachedOwnerCharacter->GetActorLocation();
	// Get the direction the character is moving
	FVector Direction = CachedOwnerCharacter->GetCharacterMovement()->GetLastInputVector().GetSafeNormal();
	if (Direction==FVector::ZeroVector)
	{
		Direction=CachedOwnerCharacter->GetCharacterMovement()->GetForwardVector().GetSafeNormal();
	}
	const FVector End=Start+Direction*SoftTargetingRange;
	
	// Set up collision to detect pawns	
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
	
	// Create a sphere collision shape
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(TargetRadius);
	
	// Ignore the player to prevent self-collision
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(CachedOwnerCharacter);

	// Perform the sphere trace
	const bool bBlockHit=CachedOwnerCharacter->GetWorld()->SweepSingleByObjectType(OutHit,Start,End,FQuat::Identity
		,ObjectQueryParams,CollisionShape,Params);

	if (bBlockHit)
	{
		if (ACharacter* HitCharacter=Cast<ACharacter>(OutHit.GetActor()))
		{
			SoftTargetedCharacter=HitCharacter;
			// Draw debug sphere at the hit location
			DrawDebugSphere(
				CachedOwnerCharacter->GetWorld(),
				OutHit.ImpactPoint,
				TargetRadius,
				12,
				FColor::Green,
				false,
				1.0f);
		}
	}
	else
	{
		SoftTargetedCharacter=nullptr;
	}
	// Draw debug line for the trace
	DrawDebugLine(CachedOwnerCharacter->GetWorld(), Start, End, FColor::Green, false, 2.0f, 0, 2.0f);
}

void UCombatComponent::RotationToSoftTarget(FGameplayEventData Payload)
{
	if (SoftTargetedCharacter)
	{
		StartRotation=CachedOwnerCharacter->GetActorRotation();
		FVector CharacterLocation=CachedOwnerCharacter->GetActorLocation();
		TargetRotation=UKismetMathLibrary::FindLookAtRotation(CharacterLocation,SoftTargetedCharacter->GetActorLocation());

		TargetRotation.Pitch = CachedOwnerCharacter->GetActorRotation().Pitch;

		RotationTimeline.PlayFromStart();
		UE_LOG(LogTemp, Warning, TEXT("UCombatComponent::RotationToSoftTarget activation by%s"), *CachedOwnerCharacter->GetName());
		// CachedOwnerCharacter->SetActorRotation(TargetRotation);
	}
	UE_LOG(LogTemp, Log, TEXT("RotationToSoftTarget called"));
}

