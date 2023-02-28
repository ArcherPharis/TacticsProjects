// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LVGameplayAbility.h"
#include "GA_Firebomb.generated.h"

/**
 * 
 */
UCLASS()
class TACTICSPROJECTS_API UGA_Firebomb : public ULVGameplayAbility
{
	GENERATED_BODY()

private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UFUNCTION()
	void StartFiringBomb(FGameplayEventData Payload);

	UFUNCTION()
	void Explosion(FGameplayEventData Payload);


	UPROPERTY(EditDefaultsOnly, Category = "FireBomb")
	UAnimMontage* CastingMontage;

	UPROPERTY(EditDefaultsOnly, Category = "FireBomb")
	TSubclassOf<UGameplayEffect> explosionEffect;

	UPROPERTY(EditDefaultsOnly, Category = "FireBomb")
	TSubclassOf<AActor> projectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "FireBomb")
	FName projectileSpawnLocationSocketName;
	UPROPERTY(EditDefaultsOnly, Category = "FireBomb")
	FGameplayTag StartFirebombTag;

	UPROPERTY(EditDefaultsOnly, Category = "FireBomb")
	FGameplayTag ExplosionTag;

};
