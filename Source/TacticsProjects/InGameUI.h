// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameUI.generated.h"

/**
 * 
 */
UCLASS()
class TACTICSPROJECTS_API UInGameUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateOxygenBar(float oxygen, float maxOxygen);
	void UpdateHealth(float health, float maxHealth);
	void UpdateCapacityBar(float capacity, float maxCapacity);
	void UpdateOxygenReserves(float newVal);
	void ToggleInventoryCanvas(bool& inInventory);

	UFUNCTION()
	void NewItemGiven(UObject* itemToAddToList, int amount);

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* healthBar;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* capacityBar;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* oxygenBar;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* crossHair;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* oxygenPercent;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* inGameCanvas;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCanvasPanel* inventoryCanvas;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UWidgetSwitcher* widgetSwitcher;

	//UPROPERTY(meta = (BindWidget))
	//class UTileView* itemList;

	
};
