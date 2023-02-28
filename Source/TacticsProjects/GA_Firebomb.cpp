// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Firebomb.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "PlayerCharacter.h"

void UGA_Firebomb::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	GetPlayerAvatar()->GetMesh()->GetAnimInstance()->Montage_Play(CastingMontage);

	UAbilityTask_WaitGameplayEvent* WaitLaunchEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, StartFirebombTag);
	if (WaitLaunchEvent)
	{
		WaitLaunchEvent->EventReceived.AddDynamic(this, &UGA_Firebomb::StartFiringBomb);
		WaitLaunchEvent->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* Expire = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, ExplosionTag, nullptr, false, false);
	if (Expire)
	{
		Expire->EventReceived.AddDynamic(this, &UGA_Firebomb::Explosion);
		Expire->ReadyForActivation();
	}


}

void UGA_Firebomb::StartFiringBomb(FGameplayEventData Payload)
{
	FActorSpawnParameters params;
	params.Owner = GetPlayerAvatar();
	AActor* projectile =  GetWorld()->SpawnActor<AActor>(projectileClass, GetPlayerAvatar()->GetProjectileSpawnLocation()->GetComponentTransform(), params);
	
	UAbilityTask_WaitGameplayEvent* WaitExplosion = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, ExplosionTag, nullptr, false, false);
	if (WaitExplosion)
	{
		WaitExplosion->EventReceived.AddDynamic(this, &UGA_Firebomb::Explosion);
		WaitExplosion->ReadyForActivation();
	}


}

void UGA_Firebomb::Explosion(FGameplayEventData Payload)
{
	if (Payload.TargetData.Num() == 0)
	{
		K2_EndAbility();
	}

	for (TSharedPtr<FGameplayAbilityTargetData>& data : Payload.TargetData.Data)
	{
		for (TWeakObjectPtr<AActor>& actorWeakPtr : data->GetActors())
		{
			AActor* HitTarget = actorWeakPtr.Get();

		}
	}


	FGameplayEffectSpecHandle handle = MakeOutgoingGameplayEffectSpec(explosionEffect, -1);
	K2_ApplyGameplayEffectSpecToTarget(handle, Payload.TargetData);

	K2_EndAbility();
}
