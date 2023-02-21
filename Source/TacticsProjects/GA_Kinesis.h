// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LVGameplayAbility.h"
#include "GA_Kinesis.generated.h"

/**
 * 
 */
UCLASS()
class TACTICSPROJECTS_API UGA_Kinesis : public ULVGameplayAbility
{
	GENERATED_BODY()

private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UPROPERTY(EditDefaultsOnly, Category = "Kinesis")
	UAnimMontage* kinesisMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Kinesis")
	UAnimMontage* launchTargetMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Kinesis")
	TSubclassOf<UActorComponent> kinesisComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Kinesis")
	FGameplayTag BeginKinesisTag;

	UPROPERTY(EditDefaultsOnly, Category = "Kinesis")
	FGameplayTag fireObjectTag;

	UPROPERTY(EditDefaultsOnly, Category = "Kinesis")
	FGameplayTag autoEndKinesisTag;

	UPROPERTY(EditDefaultsOnly, Category = "Kinesis")
	float kinesisRange = 1200.f;
	UPROPERTY(EditDefaultsOnly, Category = "Kinesis")
	float launchForce = 1200.f;

	UFUNCTION()
	void PlayerReleasedInput(float timeHeld);

	UFUNCTION()
	void MontageOut();

	UFUNCTION()
	void BeginKinesis(FGameplayEventData Payload);

	UFUNCTION()
	void LaunchTarget(FGameplayEventData Payload);

	UFUNCTION()
	void EndKinesisNoTarget(FGameplayEventData Payload);

	bool kinesisActivated;

public:
	UFUNCTION(BlueprintCallable, Category = "Kinesis")
	void ReleaseHeldItem();
};
