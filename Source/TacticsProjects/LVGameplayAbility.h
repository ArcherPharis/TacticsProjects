// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "LVGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class TACTICSPROJECTS_API ULVGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual bool CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) override;
	
	UFUNCTION(BlueprintCallable, Category = "Ability")
	class ABaseCharacter* GetBaseCharacterAvatar() const;
	UFUNCTION(BlueprintCallable, Category = "Ability")
	class APlayerCharacter* GetPlayerAvatar() const;

	ABaseCharacter* AvatarBaseCharacter;
	APlayerCharacter* PlayerCharacter;
};
