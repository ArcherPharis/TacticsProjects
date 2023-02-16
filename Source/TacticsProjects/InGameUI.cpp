// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UInGameUI::UpdateOxygenBar(float oxygen, float maxOxygen)
{
	oxygenBar->SetPercent(oxygen / maxOxygen);
}

void UInGameUI::UpdateHealth(float health, float maxHealth)
{
	healthBar->SetPercent(health / maxHealth);
}

void UInGameUI::UpdateCapacityBar(float capacity, float maxCapacity)
{
	capacityBar->SetPercent(capacity / maxCapacity);
}

void UInGameUI::UpdateOxygenReserves(float newVal)
{
	oxygenPercent->SetText(FText::FromString(FString::SanitizeFloat(FMath::RoundHalfToZero(newVal))));
}
