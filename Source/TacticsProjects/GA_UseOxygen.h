// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LVGameplayAbility.h"
#include "GA_UseOxygen.generated.h"

/**
 * 
 */
UCLASS()
class TACTICSPROJECTS_API UGA_UseOxygen : public ULVGameplayAbility
{
	GENERATED_BODY()

private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UPROPERTY(EditDefaultsOnly, Category = "UseOxygen")
	UAnimMontage* UseOxygenMontage;

	UFUNCTION()
	void MontageFinished();

	UFUNCTION()
	void RefillOxygen();
};
