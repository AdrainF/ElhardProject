// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EP_EnemyAIController.generated.h"

// Enemy states for AI behavior
UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Patrol        UMETA(DisplayName = "Patrol"),
	Idle          UMETA(DisplayName = "Idle"),
	Chasing       UMETA(DisplayName = "Chasing"),
	Investigating UMETA(DisplayName = "Investigating")
};

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;
class UAISenseConfig_Damage;
class UStateTreeAIComponent;
class AEnemyCharacterBase;
class UCombatComponent;
UCLASS()
class PROJECTELHARD_API AEP_EnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	/** Constructor */
	AEP_EnemyAIController();

protected:
	/** AI Perception component used for sensing the environment */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AISense")
	UAIPerceptionComponent* AIPerception = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category="AI")
	TObjectPtr<UStateTreeAIComponent> StateTreeComp;
	/** Configuration for sight sense */
	UPROPERTY()
	TObjectPtr<UAISenseConfig_Sight> SightConfig;

	/** Configuration for hearing sense */
	UPROPERTY()
	TObjectPtr<UAISenseConfig_Hearing> HearingConfig;

	/** Configuration for damage sense */
	UPROPERTY()
	TObjectPtr<UAISenseConfig_Damage> DamageConfig;

	/** Called when the AI perceives a target actor */
	UFUNCTION()
	void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus);

	virtual void OnPossess(APawn* InPawn) override;

	/** Called when the game starts or AI controller is spawned */
	virtual void BeginPlay() override;

	
	
public:

	UPROPERTY()
	TObjectPtr<AEnemyCharacterBase> AICharacter = nullptr;
	
	UPROPERTY()
	TObjectPtr<UCombatComponent> CombatComponent = nullptr;
	/** Set the current AI state */
	UFUNCTION(BlueprintCallable)
	void SetAIState(EEnemyState State);

	/** Get the current AI state */
	UFUNCTION(BlueprintCallable)
	EEnemyState GetAIState();

	/** Set the current target actor */
	UFUNCTION(BlueprintCallable)
	void SetTargetActor(AActor* TargetActor);

	/** Get the current target actor */
	UFUNCTION(BlueprintCallable)
	AActor* GetTargetActor();

	/** Clear the current target actor */
	UFUNCTION(BlueprintCallable)
	void ClearTarget();

	/** Handle sight perception events */
	UFUNCTION(BlueprintCallable)
	void HandleSight(AActor* Actor, const FAIStimulus& Stimulus);

	/** Handle hearing perception events */
	UFUNCTION(BlueprintCallable)
	void HandleHearing(AActor* Actor, const FAIStimulus& Stimulus);

	/** Handle damage perception events */
	UFUNCTION(BlueprintCallable)
	void HandleSDamage(AActor* Actor, const FAIStimulus& Stimulus);

	/** The current target actor that AI focuses on */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> Target = nullptr;

	/** Location to investigate when in Investigating state */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector InvestLoc;

	/** Current state of the AI */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	EEnemyState AIState = EEnemyState::Idle;
};
