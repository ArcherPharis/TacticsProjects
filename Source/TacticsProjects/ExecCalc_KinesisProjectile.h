// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalc_KinesisProjectile.generated.h"

/**
 * 
 */
UCLASS()
class TACTICSPROJECTS_API UExecCalc_KinesisProjectile : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UExecCalc_KinesisProjectile();

	void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecParams, FGameplayEffectCustomExecutionOutput& ExecOutputs) const;
};
