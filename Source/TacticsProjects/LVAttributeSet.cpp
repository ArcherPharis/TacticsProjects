// Fill out your copyright notice in the Description page of Project Settings.


#include "LVAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

void ULVAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);
    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
    }

    if (Data.EvaluatedData.Attribute == GetOxygenAttribute())
    {
        SetOxygen(FMath::Clamp(GetOxygen(), 0.f, GetMaxOxygen()));
    }


    if (Data.EvaluatedData.Attribute == GetLevelAttribute())
    {
        SetLevel(FMath::Clamp(GetLevel(), 0.f, GetMaxLevel()));
    }
}
