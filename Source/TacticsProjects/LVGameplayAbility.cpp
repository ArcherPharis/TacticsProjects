// Fill out your copyright notice in the Description page of Project Settings.


#include "LVGameplayAbility.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.h"

void ULVGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (bHasBlueprintActivate)
	{
		// A Blueprinted ActivateAbility function must call CommitAbility somewhere in its execution chain.
		K2_ActivateAbility();
	}
	else if (bHasBlueprintActivateFromEvent)
	{
		if (TriggerEventData)
		{
			// A Blueprinted ActivateAbility function must call CommitAbility somewhere in its execution chain.
			K2_ActivateAbilityFromEvent(*TriggerEventData);
		}
		else
		{
			UE_LOG(LogAbilitySystem, Warning, TEXT("Ability %s expects event data but none is being supplied. Use Activate Ability instead of Activate Ability From Event."), *GetName());
			bool bReplicateEndAbility = false;
			bool bWasCancelled = true;
			EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
		}
	}

	AvatarBaseCharacter = Cast<ABaseCharacter>(ActorInfo->AvatarActor);
}

bool ULVGameplayAbility::CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags)
{
	bool commitSuccess = Super::CommitAbility(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags);
	return commitSuccess;
}

ABaseCharacter* ULVGameplayAbility::GetBaseCharacterAvatar() const
{
	if (AvatarBaseCharacter == nullptr)
	{
		return Cast<ABaseCharacter>(GetAvatarActorFromActorInfo());
	}
	return AvatarBaseCharacter;
}

APlayerCharacter* ULVGameplayAbility::GetPlayerAvatar() const
{
	if (PlayerCharacter == nullptr)
	{
		return Cast<APlayerCharacter>(GetAvatarActorFromActorInfo());
	}
	return PlayerCharacter;
}
