// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayEffectTypes.h"
#include "LVPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TACTICSPROJECTS_API ALVPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void OnPossess(APawn* newPawn) override;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ToggleUIInventory();

	UFUNCTION(BlueprintPure, Category = "PlayerController")
	class UInGameUI* GetUI() const { return inGameUI; }

private:
	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<class UInGameUI> inGameUIClass;
	
	UInGameUI* inGameUI;

	class APlayerCharacter* playerCharacter;

	void OxygenUpdated(const FOnAttributeChangeData& AttributeData);
	void HealthUpdated(const FOnAttributeChangeData& AttributeData);
	void CapacityUpdated(const FOnAttributeChangeData& AttributeData);

	virtual void SetupInputComponent() override;

	UFUNCTION()
	void OxygenReserveUpdated(float oxy);



	UFUNCTION()
	void AddNewItemToInventoryList(UObject* itemToAdd, AActor* InventoryOwner);
	
};
