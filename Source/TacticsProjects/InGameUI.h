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
	void UpdateOxygenReserves(float newVal);

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

	
};
