// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "GameFramework/Actor.h"
#include "EP_WeaponBase.generated.h"

class USkeletalMeshComponent;
UCLASS()
class PROJECTELHARD_API AEP_WeaponBase : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AEP_WeaponBase();

	UPROPERTY(EditDefaultsOnly,Category="Config")
	TObjectPtr<class UEP_WeaponConfig_DataAsset> WeaponConfig;
	
	UPROPERTY(EditDefaultsOnly,Category="Collison")
	USceneComponent* Start_Collision;

	UPROPERTY(EditDefaultsOnly,Category="Collison")
	USceneComponent* End_Collision;
	
	UPROPERTY(EditDefaultsOnly,Category="AttackAnimations")
	TArray<TObjectPtr<UAnimMontage>> AttackAnimations;

	UPROPERTY(EditDefaultsOnly,Category="Mesh")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

protected:
	UPROPERTY()
	bool bStartWeaponTrace=false;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	TArray<UAnimMontage*> GetAttackAnimations() const { return AttackAnimations; }
	UFUNCTION(BlueprintCallable)
	void WeaponTrace(ACharacter* OwnerCharacter);
	UFUNCTION(BlueprintCallable)
	bool IsStartWeaponTrace() const { return bStartWeaponTrace; }
	UFUNCTION(BlueprintCallable)
	void StartWeaponTrace(FGameplayEventData Payload){bStartWeaponTrace = true;}
	UFUNCTION(BlueprintCallable)
	void StopWeaponTrace(FGameplayEventData Payload){bStartWeaponTrace = false;}
	
	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
