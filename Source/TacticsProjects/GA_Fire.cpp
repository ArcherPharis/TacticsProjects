// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Fire.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "LVAbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "GameFramework./CharacterMovementComponent.h"
#include "BaseProjectile.h"
#include "PlayerCharacter.h"

void UGA_Fire::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAbilityTask_PlayMontageAndWait* MontagePlay = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, FireAttackMontage);
	if (MontagePlay)
	{
		MontagePlay->OnBlendOut.AddDynamic(this, &UGA_Fire::MontageFinished);
		MontagePlay->OnCancelled.AddDynamic(this, &UGA_Fire::MontageFinished);
		MontagePlay->OnInterrupted.AddDynamic(this, &UGA_Fire::MontageFinished);
		MontagePlay->OnCompleted.AddDynamic(this, &UGA_Fire::MontageFinished);
		MontagePlay->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* WaitComboChange = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, ComboChangeTag, nullptr, false, false);
	if (WaitComboChange)
	{
		WaitComboChange->EventReceived.AddDynamic(this, &UGA_Fire::UpdateCombo);
		WaitComboChange->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* WaitComboCommit = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, ComboCommitTag, nullptr, false, false);
	if (WaitComboCommit)
	{
		WaitComboCommit->EventReceived.AddDynamic(this, &UGA_Fire::ComboCommit);
		WaitComboCommit->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* WaitProjectileSpawnEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, ProjectileLaunchTag, nullptr, false, false);
	if (WaitProjectileSpawnEvent)
	{
		WaitProjectileSpawnEvent->EventReceived.AddDynamic(this, &UGA_Fire::LaunchProjectile);
		WaitProjectileSpawnEvent->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* WaitDamageEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, ProjectileDamageTag, nullptr, false, false);
	if (WaitDamageEvent)
	{
		WaitDamageEvent->EventReceived.AddDynamic(this, &UGA_Fire::ApplyEffects);
		WaitDamageEvent->ReadyForActivation();
	}

}

void UGA_Fire::MontageFinished()
{
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}

void UGA_Fire::UpdateCombo(FGameplayEventData Payload)
{
	NextComboSectionName = ULVAbilitySystemBlueprintLibrary::GetRandomNameFromTagContainer(Payload.TargetTags);
}

void UGA_Fire::ComboCommit(FGameplayEventData Payload)
{
	if (NextComboSectionName == NAME_None)
		return;

	USkeletalMeshComponent* mesh = GetOwningComponentFromActorInfo();
	if (mesh)
	{
		UAnimInstance* AnimBP = mesh->GetAnimInstance();
		if (AnimBP->Montage_GetCurrentSection() == NextComboSectionName)
		{
			return;
		}

		if (AnimBP && AnimBP->GetCurrentActiveMontage())
		{
			AnimBP->Montage_SetNextSection(AnimBP->Montage_GetCurrentSection(), NextComboSectionName, AnimBP->GetCurrentActiveMontage());
			AnimBP->Montage_JumpToSection(NextComboSectionName, AnimBP->GetCurrentActiveMontage());
		}
	}
}

void UGA_Fire::LaunchProjectile(FGameplayEventData Payload)
{
	FActorSpawnParameters params;
	params.Owner = GetBaseCharacterAvatar();
	projectile = GetWorld()->SpawnActor<ABaseProjectile>(projectileActorClass, GetBaseCharacterAvatar()->GetProjectileSpawnLocation()->GetComponentTransform(), params);
}

void UGA_Fire::ApplyEffects(FGameplayEventData Payload)
{

	if (Payload.TargetData.Num() == 0) return;

	for (TSharedPtr<FGameplayAbilityTargetData>& data : Payload.TargetData.Data)
	{
		for (TWeakObjectPtr<AActor>& actorWeakPtr : data->GetActors())
		{
			AActor* HitTarget = actorWeakPtr.Get();

		}
	}


	FGameplayEffectSpecHandle handle = MakeOutgoingGameplayEffectSpec(damageEffect);
	K2_ApplyGameplayEffectSpecToTarget(handle, Payload.TargetData);
}
