// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LVGameplayAbility.h"
#include "GA_Fire.generated.h"

/**
 * 
 */
UCLASS()
class TACTICSPROJECTS_API UGA_Fire : public ULVGameplayAbility
{
	GENERATED_BODY()

private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	UAnimMontage* FireAttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	FGameplayTag ComboChangeTag;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	FGameplayTag ComboCommitTag;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	FGameplayTag ProjectileLaunchTag;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	FGameplayTag ProjectileDamageTag;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<UGameplayEffect> damageEffect;

	UFUNCTION()
	void MontageFinished();

	UFUNCTION()
	void UpdateCombo(FGameplayEventData Payload);

	UFUNCTION()
	void ComboCommit(FGameplayEventData Payload);

	UFUNCTION()
	void LaunchProjectile(FGameplayEventData Payload);

	UFUNCTION()
	void ApplyEffects(FGameplayEventData Payload);

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class ABaseProjectile> projectileActorClass;

	ABaseProjectile* projectile;
	FName NextComboSectionName;

	

};
