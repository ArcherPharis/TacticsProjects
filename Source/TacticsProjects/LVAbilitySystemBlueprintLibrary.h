// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "LVAbilitySystemBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TACTICSPROJECTS_API ULVAbilitySystemBlueprintLibrary : public UAbilitySystemBlueprintLibrary
{
	GENERATED_BODY()
	
public:
	static FName GetTagNameLast(const FGameplayTag& Tag);
	static FName GetRandomNameFromTagContainer(const FGameplayTagContainer& container);
};
