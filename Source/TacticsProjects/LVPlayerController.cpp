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

void ALVPlayerController::OxygenReserveUpdated(float oxy)
{
	UE_LOG(LogTemp, Warning, TEXT("Getting to character controller: %f"), oxy);
	inGameUI->UpdateOxygenReserves(oxy);
}