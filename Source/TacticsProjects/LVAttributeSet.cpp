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

    if (Data.EvaluatedData.Attribute == GetCapcityAttribute())
    {
        SetCapcity(FMath::Clamp(GetCapcity(), 0.f, GetMaxCapacity()));
    }

    if (Data.EvaluatedData.Attribute == GetNourishmentAttribute())
    {
        SetNourishment(FMath::Clamp(GetNourishment(), 0.f, GetMaxNourishment()));
    }


    if (Data.EvaluatedData.Attribute == GetLevelAttribute())
    {
        SetLevel(FMath::Clamp(GetLevel(), 0.f, GetMaxLevel()));
    }
}
