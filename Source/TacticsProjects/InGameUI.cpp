// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UInGameUI::UpdateOxygenBar(float oxygen, float maxOxygen)
{
	oxygenBar->SetPercent(oxygen / maxOxygen);
}

void UInGameUI::UpdateOxygenReserves(float newVal)
{
	oxygenPercent->SetText(FText::FromString(FString::SanitizeFloat(FMath::RoundHalfToZero(newVal))));
}
