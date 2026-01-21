// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "CombatComponent.generated.h"

class UGameplayAbility;
class AWeaponBase;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTELHARD_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSaveAttack = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat")
	float SoftTargetingRange = 500.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat")
	float TargetRadius = 100.f;
	
	UPROPERTY()
	ACharacter* SoftTargetedCharacter=nullptr;
protected:

	// Rotation Curve for smooth rotation
	UPROPERTY(EditAnywhere, Category = "Soft Targeting|Rotation")
	UCurveFloat* RotationCurve;
	// Rotation variables
	UPROPERTY()
	FRotator StartRotation;
	UPROPERTY()
	FRotator TargetRotation;
	
	// Timeline
	FTimeline RotationTimeline;
	UPROPERTY()
	TObjectPtr<AWeaponBase> EquippedWeapon=nullptr;
	UPROPERTY()
	TObjectPtr<ACharacter> CachedOwnerCharacter=nullptr;


	UFUNCTION()
	void HandleRotationProgress(float Value);
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void EquipWeapon(AWeaponBase* Weapon);

	UFUNCTION(Blueprintable,Category = "Weapon")
	AWeaponBase* GetEquippedWeapon() const { return EquippedWeapon; }
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable,Category = "Combat")
	void SoftTargeting();

	UFUNCTION(BlueprintCallable,Category = "Combat")
	void RotationToSoftTarget(FGameplayEventData Payload);
		
};
