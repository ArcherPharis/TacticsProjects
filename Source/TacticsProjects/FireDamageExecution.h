// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "FireDamageExecution.generated.h"

/**
 * 
 */
UCLASS()
class TACTICSPROJECTS_API UFireDamageExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:

	UFireDamageExecution();

	void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecParams, FGameplayEffectCustomExecutionOutput& ExecOutputs) const;
	
};
