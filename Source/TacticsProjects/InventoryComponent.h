// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseItem.h"
#include "InventoryComponent.generated.h"

class ABaseItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TACTICSPROJECTS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void AddToInventory(ABaseItem* itemToAdd, int amount);
	UFUNCTION(BlueprintCallable)
	bool QueryInventory(ABaseItem* itemToQuery, int amount, int& QuanityOfItem);
	UFUNCTION(BlueprintCallable)
	void RemoveFromInventory(ABaseItem* itemToRemove, int amount);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TMap<ABaseItem*, int> Inventory;
};
