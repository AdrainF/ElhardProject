// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/EP_EnemyAIController.h"

#include "Characters/EnemyCharacterBase.h"
#include "Characters/PlayerCharacter.h"
#include "Components/CombatComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "GameplayStateTreeModule/Public/Components/StateTreeAIComponent.h"




AEP_EnemyAIController::AEP_EnemyAIController()
{
	// Create and configure the perception component
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AISense"));

	// === SIGHT CONFIGURATION ===
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 1500.0f;
	SightConfig->LoseSightRadius = 1800.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	// === HEARING CONFIGURATION ===
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
	HearingConfig->HearingRange = 2000.0f;
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;

	// === DAMAGE CONFIGURATION ===
	DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("DamageConfig"));
	// No extra config required for damage

	// === CONFIGURE AI PERCEPTION ===
	AIPerception->ConfigureSense(*SightConfig);
	AIPerception->ConfigureSense(*HearingConfig);
	AIPerception->ConfigureSense(*DamageConfig);
	AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());

	StateTreeComp= CreateDefaultSubobject<UStateTreeAIComponent>(TEXT("StateTreeComp"));

	// Bind perception updated event
	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AEP_EnemyAIController::OnTargetPerceived);


}
// Called when the AI perceives a target actor
void AEP_EnemyAIController::OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus)
{
	// Ignore perception if the owner character is dead
	if (AICharacter->bIsDead)
	{return;}
	
	const FAISenseID SenseID = Stimulus.Type;

	// Get the IDs for each sense type
	const FAISenseID SightID = UAISense::GetSenseID(UAISense_Sight::StaticClass());
	const FAISenseID HearingID = UAISense::GetSenseID(UAISense_Hearing::StaticClass());
	const FAISenseID DamageID = UAISense::GetSenseID(UAISense_Damage::StaticClass());

	// Handle the perception event depending on the sense
	if (SenseID == SightID)
	{
		HandleSight(Actor, Stimulus);
	}
	else if (SenseID == HearingID)
	{
		HandleHearing(Actor, Stimulus);
	}
	else if (SenseID == DamageID)
	{
		HandleSDamage(Actor, Stimulus);
	}
}

void AEP_EnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Cache player character
	AICharacter = Cast<AEnemyCharacterBase>(GetPawn());
	checkf(AICharacter, TEXT("AEP_EnemyAIController cant cast owner to AEnemyCharacterBase"));
	
	// Cache combat component
	CombatComponent = AICharacter->GetCombatComponent();
}

void AEP_EnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEP_EnemyAIController::SetAIState(EEnemyState State)
{
	// Update the AI state if it has changed
	if (AIState != State)
	{
		AIState = State;
	}
}

EEnemyState AEP_EnemyAIController::GetAIState()
{
	return AIState;
}

void AEP_EnemyAIController::SetTargetActor(AActor* TargetActor)
{
	// Update the target actor if it has changed
	if (Target != TargetActor)
	{
		Target = TargetActor;
	}
}

AActor* AEP_EnemyAIController::GetTargetActor()
{
	return Target;
}

void AEP_EnemyAIController::ClearTarget()
{
	Target = nullptr;
}
// Handle sight perception events
void AEP_EnemyAIController::HandleSight(AActor* Actor, const FAIStimulus& Stimulus)
{
	// Check if the stimulus was successfully sensed
	if (Stimulus.WasSuccessfullySensed())
	{
		UE_LOG(LogTemp, Warning, TEXT("Saw %s"), *Actor->GetName());
		// If the actor is a player character, set as target and switch to chasing state
		if (TSoftObjectPtr<APlayerCharacter> Player = Cast<APlayerCharacter>(Actor))
		{
			SetTargetActor(Actor);
			SetAIState(EEnemyState::Chasing);
			

			
			checkf(CombatComponent, TEXT("Cannot get CombatComponent from AICharacter"));
			if (CombatComponent)
			{
				CombatComponent->SoftTargetedCharacter=Cast<ACharacter>(Actor);
			}
		}
	}
}
// Handle hearing perception events
void AEP_EnemyAIController::HandleHearing(AActor* Actor, const FAIStimulus& Stimulus)
{
	// Check if the stimulus was successfully sensed
	if (Stimulus.WasSuccessfullySensed())
	{
		// Set the AI state to investigating and store the location of the noise
		SetAIState(EEnemyState::Investigating);
		InvestLoc = Stimulus.StimulusLocation;
		UE_LOG(LogTemp, Warning, TEXT("Heard a noise from %s"), *Actor->GetName());
		
	}
}
// Handle damage perception events
void AEP_EnemyAIController::HandleSDamage(AActor* Actor, const FAIStimulus& Stimulus)
{
	// Check if the stimulus was successfully sensed
	if (Stimulus.WasSuccessfullySensed())
	{
		// If the actor is a player character, set as target and switch to chasing state
		if (TSoftObjectPtr <APlayerCharacter> Player = Cast<APlayerCharacter>(Actor))
		{
			SetTargetActor(Actor);
			SetAIState(EEnemyState::Chasing);
			UE_LOG(LogTemp, Warning, TEXT("Received damage from %s"), *Actor->GetName());
		}
	}
}
