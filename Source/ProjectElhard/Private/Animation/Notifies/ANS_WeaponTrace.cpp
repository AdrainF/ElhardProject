// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notifies/ANS_WeaponTrace.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"


void UANS_WeaponTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (MeshComp)
	{
		if (ACharacter* OwnerCharacter = Cast<ACharacter>(MeshComp->GetOwner()))
		{
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerCharacter, FGameplayTag::RequestGameplayTag("Event.WeaponTrace.Start"), FGameplayEventData());
		
		}
	}
}

void UANS_WeaponTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		if (ACharacter* OwnerCharacter = Cast<ACharacter>(MeshComp->GetOwner()))
		{
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerCharacter, FGameplayTag::RequestGameplayTag("Event.WeaponTrace.End"), FGameplayEventData());
		
		}
	}
}
