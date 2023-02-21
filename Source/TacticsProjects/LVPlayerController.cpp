// Fill out your copyright notice in the Description page of Project Settings.


#include "LVPlayerController.h"
#include "PlayerCharacter.h"
#include "LVAbilitySystemComponent.h"
#include "LVAttributeSet.h"
#include "InGameUI.h"

void ALVPlayerController::OnPossess(APawn* newPawn)
{
	Super::OnPossess(newPawn);

	playerCharacter = Cast<APlayerCharacter>(newPawn);
	if (playerCharacter)
	{
		playerCharacter->GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(playerCharacter->GetAttributeSet()->GetOxygenAttribute()).AddUObject(this, &ALVPlayerController::OxygenUpdated);
		playerCharacter->GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(playerCharacter->GetAttributeSet()->GetHealthAttribute()).AddUObject(this, &ALVPlayerController::HealthUpdated);
		playerCharacter->GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(playerCharacter->GetAttributeSet()->GetCapcityAttribute()).AddUObject(this, &ALVPlayerController::CapacityUpdated);
		playerCharacter->onOxygenChange.AddDynamic(this, &ALVPlayerController::OxygenReserveUpdated);

	}
}

void ALVPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (inGameUIClass)
	{
		inGameUI = CreateWidget<UInGameUI>(this, inGameUIClass);
		inGameUI->AddToViewport();
	}
}

void ALVPlayerController::OxygenUpdated(const FOnAttributeChangeData& AttributeData)
{
	inGameUI->UpdateOxygenBar(AttributeData.NewValue, playerCharacter->GetAttributeSet()->GetMaxOxygen());
}

void ALVPlayerController::HealthUpdated(const FOnAttributeChangeData& AttributeData)
{
	inGameUI->UpdateHealth(AttributeData.NewValue, playerCharacter->GetAttributeSet()->GetMaxHealth());
}

void ALVPlayerController::CapacityUpdated(const FOnAttributeChangeData& AttributeData)
{
	inGameUI->UpdateCapacityBar(AttributeData.NewValue, playerCharacter->GetAttributeSet()->GetMaxCapacity());
}

void ALVPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		FInputActionBinding& InventoryInputBind = InputComponent->BindAction("Inventory", IE_Pressed, this, &ALVPlayerController::ToggleUIInventory);
		InventoryInputBind.bExecuteWhenPaused = true;
	}

}

void ALVPlayerController::OxygenReserveUpdated(float oxy)
{
	inGameUI->UpdateOxygenReserves(oxy);
}

void ALVPlayerController::ToggleUIInventory()
{
	bool inInv;
	inGameUI->ToggleInventoryCanvas(inInv);
	if (inInv)
	{
		SetInputMode(FInputModeGameAndUI());
		SetPause(true);
		bShowMouseCursor = true;
	}
	else
	{
		SetInputMode(FInputModeGameOnly());
		SetPause(false);
		bShowMouseCursor = false;

	}
}
