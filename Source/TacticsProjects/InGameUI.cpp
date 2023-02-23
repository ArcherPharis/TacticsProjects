// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Components/CanvasPanel.h"
#include "Components/TileView.h"
#include "ItemEntry.h"



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

void UInGameUI::ToggleInventoryCanvas(bool& inInventory)
{
	if (widgetSwitcher->GetActiveWidget() == inGameCanvas)
	{
		widgetSwitcher->SetActiveWidget(inventoryCanvas);
		inInventory = true;
		return;
	}
	if (widgetSwitcher->GetActiveWidget() == inventoryCanvas)
	{
		widgetSwitcher->SetActiveWidget(inGameCanvas);
	}
	inInventory = false;
}

void UInGameUI::NewItemGiven(UObject* itemToAddToList, int amount)
{
	//itemList->AddItem(itemToAddToList);

}

