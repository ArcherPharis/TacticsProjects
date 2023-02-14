// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_UseOxygen.h"
#include "LVAbilitySystemBlueprintLibrary.h"
#include "PlayerCharacter.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"

void UGA_UseOxygen::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (GetPlayerAvatar()->HasReservedOxygen())
	{
		UAbilityTask_PlayMontageAndWait* MontagePlay = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, UseOxygenMontage);
		if (MontagePlay)
		{
			MontagePlay->OnCancelled.AddDynamic(this, &UGA_UseOxygen::MontageFinished);
			MontagePlay->OnInterrupted.AddDynamic(this, &UGA_UseOxygen::MontageFinished);
			MontagePlay->OnCompleted.AddDynamic(this, &UGA_UseOxygen::RefillOxygen);
			MontagePlay->ReadyForActivation();
		}
	}
	else
	{
		K2_EndAbility();
	}
}

void UGA_UseOxygen::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_UseOxygen::MontageFinished()
{
	K2_EndAbility();

}

void UGA_UseOxygen::RefillOxygen()
{
	GetPlayerAvatar()->RefillOxygen();
	K2_EndAbility();
}
