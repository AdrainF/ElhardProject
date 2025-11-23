// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notifies/AN_RotateToTarget.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"

void UAN_RotateToTarget::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		if (ACharacter* OwnerCharacter = Cast<ACharacter>(MeshComp->GetOwner()))
		{
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerCharacter, FGameplayTag::RequestGameplayTag("Event.Rotation")
				, FGameplayEventData());
		
		}
	}
}
